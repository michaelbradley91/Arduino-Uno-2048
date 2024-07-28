#include <unity.h>
#include <Arduino.h>
#include <CException.h>
#include <InputFake.hpp>
#include <Graphics.hpp>
#include <pins.h>
#include <game_state.h>
#include <util.h>

extern void main_setup(void);
extern void main_loop(void);
extern GameState game_state;

/**
 * @brief Top level tests to exercise the full functionality of the game
 *        by simulating user input
 */
void test_setup_initialise_graphics_and_input_and_start_scene()
{
    /* We mock input, so just expect the correct call */
    init_input_Expect(WOKWI_PIN, IR_RECEIVE_PIN);

    /* Trigger initial setup */
    main_setup();

    /* Test the scene is correct */
    TEST_ASSERT_EQUAL(SCENE_START, game_state.scene);

    /* Try drawing some more text */
    position pos = {x: 0, y: 0};
    draw_text("H", &pos);
    delay(200);

    /* Verify the text appeared, and so the graphics work correctly */
    lcd_state state = get_current_lcd_state();
    TEST_ASSERT_EQUAL_CHAR('H', state.grid[0][0]);
}

/**
 * @brief Test that we play the game and everything at least basically works?
 *        We sleep between button presses for dramatic effect... :D
 */
void test_can_play_game_and_return_to_menu()
{
    /* Initialise the program again */
    init_input_Expect(WOKWI_PIN, IR_RECEIVE_PIN);
    main_setup();
    delay(1000);

    /* Press a button so that we can begin playing */
    get_button_pressed_ExpectAndReturn(BUTTON_ENTER);
    main_loop();
    delay(1000);

    /* Check we have started playing */
    TEST_ASSERT_EQUAL(SCENE_PLAY, game_state.scene);

    /* Check the game has started with 2 numbers in the grid */
    int numbers_found = 0;
    for (int x = 0; x < 4; x++)
    {
        for (int y = 0; y < 4; y++)
        {
            if (game_state.grid.cells[x][y] > 0)
            {
                numbers_found++;
            }
            /* We'll actually fix up the game state for the next part of the test, so clear the cells we found*/
            game_state.grid.cells[x][y] = 0;
        }
    }
    TEST_ASSERT_EQUAL_MESSAGE(2, numbers_found, "Game should have started with two numbers");

    /* Simulate sliding a number */
    game_state.grid.cells[0][0] = 2;
    game_state.grid.cells[0][1] = 2;

    /* Press down to combine the two 2's */
    get_button_pressed_ExpectAndReturn(BUTTON_DOWN);
    main_loop();
    delay(1000);

    /* Confirm the numbers slid and combined */
    TEST_ASSERT_EQUAL(0, game_state.grid.cells[0][0]);
    TEST_ASSERT_EQUAL(0, game_state.grid.cells[0][1]);
    TEST_ASSERT_EQUAL(4,  game_state.grid.cells[0][3]);

    /* Finally return back to the start menu */
    get_button_pressed_ExpectAndReturn(BUTTON_BACK);
    main_loop();
    delay(1000);

    /* Check we arrived at the start scene */
    TEST_ASSERT_EQUAL(SCENE_START, game_state.scene);
}