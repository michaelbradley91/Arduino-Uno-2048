#include <Arduino.h>
#include <Input.hpp>
#include <Graphics.hpp>
#include <game_state.h>
#include <util.h>
#include <pins.h>

/**
 * @brief The delay beyween reading Infrared inputs. Avoids
 *        accidental double button presses.
 */
#define INPUT_DELAY_MILLISECONDS 1000

/**
 * @brief How the LCD display is connected
 */
STATIC lcd_pins graphics_pins = LCD_PINS;

/**
 * @brief The game state, reset on start up
 */
STATIC GameState game_state = {};

/**
 * @brief Whether or not the game is powered on
 */
STATIC byte powered = 1;

/**
 * @brief Initialise the game
 */
void MAIN_SETUP()
{
    SERIAL_BEGIN(115200);
    init_input(WOKWI_PIN, IR_RECEIVE_PIN);
    init_graphics(graphics_pins);
    reset_game_state(&game_state);
    update_scene(&game_state, SCENE_START);
}

/**
 * @brief Run as fast as possible.
 */
void MAIN_LOOP()
{
    /* Look for an input button */
    button button_pressed = get_button_pressed();

    if (button_pressed == BUTTON_POWER)
    {
        if (powered)
        {
            Serial.println("Powering down");
            turn_off_screen();
            powered = 0;
            return;
        }
        Serial.println("Powering up!");
        reset_screen();
        turn_on_screen();
        reset_game_state(&game_state);        
        powered = 1;
    }

    /* If we're not powered, we can ignore all other buttons */
    if (!powered) return;

    /* Update the scene if needed */
    if (button_pressed != BUTTON_NONE &&
        button_pressed != BUTTON_POWER)
    {
        game_state.updater(&game_state, button_pressed);
    }

    /* Render the scene */
    game_state.renderer(&game_state);
}
