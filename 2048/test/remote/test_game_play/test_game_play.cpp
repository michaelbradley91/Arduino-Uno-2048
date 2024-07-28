#include <unity.h>
#include <Arduino.h>
#include <CException.h>
#include <InputFake.hpp>
#include <Graphics.hpp>
#include <pins.h>
#include <game_state.h>
#include <util.h>

extern void main_setup(void);
extern GameState game_state;

/**
 * @brief Top level tests to exercise the full functionality of the game
 *        by simulating user input
 */
void test_setup_initialise_graphics_and_input_and_start_scene()
{
    /* We mock input, so just expect the correct call */
    init_input_Expect(WOKWI_PIN, IR_RECEIVE_PIN);
    // TEST_MESSAGE("Starting test run");
    Serial.println("Hello world");
    /* Run the setup funtion */
    main_setup();
    delay(1000);
    Serial.println("Hello again");
    delay(1000);
    Serial.println("And again");
    init_input(WOKWI_PIN, IR_RECEIVE_PIN);
    delay(1000);
    Serial.println("Going");
    delay(1000);
    init_graphics(LCD_PINS);
    delay(1000);
    Serial.println("All good");
    // reset_game_state(&game_state);

    // // /* Test the scene is correct */
    // TEST_ASSERT_EQUAL(SCENE_START, game_state.scene);

    // /* Try drawing some more text */
    // position pos = {x: 0, y: 0};
    // draw_text("H", &pos);
    // delay(200);

    // /* Verify the text appeared, and so the graphics work correctly */
    // lcd_state state = get_current_lcd_state();
    // TEST_ASSERT_EQUAL_CHAR('H', state.grid[0][0]);
}
