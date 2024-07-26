/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystalHelloWorld

*/
#define IR_RECEIVE_PIN 7
#define WOKWI_PIN 13

#include <Arduino.h>
#include <Input.hpp>
#include <Graphics.hpp>
#include <game_state.h>
#include <util.h>

/**
 * @brief How the LCD display is connected
 */
lcd_pins graphics_pins = {
    register_select : 12,
    enable : 11,
    d4 : 5,
    d5 : 4,
    d6 : 3,
    d7 : 2
};

/**
 * @brief The game state, reset on start up
 */
GameState game_state = {};

/**
 * @brief Whether or not the game is powered on
 */
byte powered = 1;

/**
 * @brief Initialise the game
 */
void setup()
{
    Serial.begin(9600);

    init_input(WOKWI_PIN, IR_RECEIVE_PIN);
    init_graphics(graphics_pins);
    reset_game_state(&game_state);
    update_scene(&game_state, SCENE_START);

    // Print a message to the LCD.
    // draw_character(LEFT_BORDER, {x : 1, y : 0});
    // draw_character(LEFT_BORDER, {x : 1, y : 1});
    // draw_character(RIGHT_BORDER, {x : 6, y : 0});
    // draw_character(RIGHT_BORDER, {x : 6, y : 1});
    // draw_character(LEFT_BORDER, {x : 9, y : 0});
    // draw_character(LEFT_BORDER, {x : 9, y : 1});
    // draw_character(RIGHT_BORDER, {x : 14, y : 0});
    // draw_character(RIGHT_BORDER, {x : 14, y : 1});
    // draw_character(RIGHT_ARROW, {x : 7, y : 1});
    // draw_character(RIGHT_ARROW, {x : 8, y : 0});
}

/**
 * @brief Run as fast as possible.
 */
void loop()
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
    if (button_pressed != BUTTON_UNKNOWN &&
        button_pressed != BUTTON_NONE &&
        button_pressed != BUTTON_POWER)
    {
        game_state.updater(&game_state, button_pressed);
    }

    /* Render the scene */
    game_state.renderer(&game_state);
}
