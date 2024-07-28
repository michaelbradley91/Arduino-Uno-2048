#include <unity.h>
#include <GraphicsFake.hpp>
#include <GraphicsStub.hpp>
#include <InputFake.hpp>
#include <game_state.h>
#include <pins.h>

extern void main_setup(void);
extern void main_loop(void);
extern GameState game_state;

/**
 * @brief Automatically use the graphics stub to track screen changes
 */
void setUp()
{
    memset(&game_state, 0, sizeof(game_state));
    init_graphics_stub();
}

/**
 * @brief Test that when the program is started, the start scene is shown
 */
void test_setup_displays_start_scene()
{
    /* Invoke the setup routine */
    init_input_Expect(WOKWI_PIN, IR_RECEIVE_PIN);
    init_graphics_Expect(LCD_PINS);
    main_setup();

    /* Check we are on the start scene */
    TEST_ASSERT_EQUAL(SCENE_START, game_state.scene);
}

/**
 * @brief Test that when the power button is pressed, the screen is toggled on and off.
 *        When the screen comes on, the game should be reset.
 */
void test_power_button_toggles_screen_on_and_off()
{
    /* Initialise the program */
    init_input_Expect(WOKWI_PIN, IR_RECEIVE_PIN);
    init_graphics_Expect(LCD_PINS);
    main_setup();

    /* Pretend to move to the play screen */
    game_state.scene = SCENE_PLAY;

    /* Prepare to power off */
    get_button_pressed_ExpectAndReturn(BUTTON_POWER);
    turn_off_screen_Expect();
    main_loop();

    /* Turn the power back on, expecting the game to be reset */
    get_button_pressed_ExpectAndReturn(BUTTON_POWER);
    turn_on_screen_Expect();
    main_loop();
    
    /* Check we have returned to the start scene */
    TEST_ASSERT_EQUAL(game_state.scene, SCENE_START);
}