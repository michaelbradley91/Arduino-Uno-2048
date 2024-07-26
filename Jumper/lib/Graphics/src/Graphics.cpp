
#include "Graphics.hpp"
#include <Arduino.h>
#include <LiquidCrystal.h>


/**
 * @brief Custom characters
 */
byte left_border[]         = { B00110, B00110, B00110, B00110, B00110, B00110, B00110, B00110 };
byte right_border[]        = { B01100, B01100, B01100, B01100, B01100, B01100, B01100, B01100 };
byte num_16[]              = { B11111, B10001, B10001, B10001, B10001, B10001, B10001, B11111 };
byte num_32[]              = { B11111, B10001, B10001, B10001, B10001, B10001, B11111, B11111 };
byte num_64[]              = { B11111, B10001, B10001, B10001, B10001, B11111, B11111, B11111 };
byte num_128[]             = { B11111, B10001, B10001, B10001, B11111, B11111, B11111, B11111 };
byte num_256[]             = { B11111, B10001, B10001, B11111, B11111, B11111, B11111, B11111 };
byte num_512[]             = { B11111, B10001, B11111, B11111, B11111, B11111, B11111, B11111 };
byte trophy_top_left[] = { B00000, B00000, B00011, B00111, B11111, B10111, B10111, B01111 };
byte trophy_top_right[] = { B00000, B00000, B11000, B11100, B11111, B11101, B11101, B11110 };
byte trophy_bottom_left[] = { B00111, B00011, B00001, B00001, B00001, B00111, B11111, B00000 };
byte trophy_bottom_right[] = { B11100, B11000, B10000, B10000, B10000, B11100, B11111, B00000 };

/**
 * @brief The liquid crystal display itself
 */
static LiquidCrystal lcd(0, 0, 0, 0, 0, 0);

/**
 * @brief We keep a record of which characters are drawn where
 */
static lcd_state state;

/**
 * @brief Initialise the graphics library
 * 
 * @param pins details of how the pins are connected to the LCD display
 */
void init_graphics(lcd_pins pins)
{
    lcd = LiquidCrystal(pins.register_select, pins.enable, pins.d4, pins.d5, pins.d6, pins.d7);
    lcd.begin(LCD_WIDTH, LCD_HEIGHT);
    reset_screen();
}

/**
 * @brief Use the play character set. This supports extra "numbers"
 *        to reach 2048
 */
void use_play_characters(void)
{
    lcd.createChar(LEFT_BORDER, left_border);
    lcd.createChar(RIGHT_BORDER, right_border);
    lcd.createChar(NUM_16, num_16);
    lcd.createChar(NUM_32, num_32);
    lcd.createChar(NUM_64, num_64);
    lcd.createChar(NUM_128, num_128);
    lcd.createChar(NUM_256, num_256);
    lcd.createChar(NUM_512, num_512);
}

/**
 * @brief Use the "win" character set to make the player feel amazing!
 */
void use_win_characters(void)
{
    lcd.createChar(TROPHY_TOP_LEFT, trophy_top_left);
    lcd.createChar(TROPHY_TOP_RIGHT, trophy_top_right);
    lcd.createChar(TROPHY_BOTTOM_LEFT, trophy_bottom_left);
    lcd.createChar(TROPHY_BOTTOM_RIGHT, trophy_bottom_right);
}

/**
 * @brief Turn off the LCD screen. Does not clear the screen
 */
void turn_off_screen(void)
{
    Serial.println("Turning screen off");
    lcd.noDisplay();
}

/**
 * @brief Turn the LCD screen back on, with whatever characters were there before
 */
void turn_on_screen(void)
{
    lcd.display();
}

/**
 * @brief Reset the LCD screen entirely, wiping all characters
 */
void reset_screen(void)
{
    lcd.clear();
    for (int x = 0; x < LCD_WIDTH; x++)
    {
        for (int y = 0; y < LCD_HEIGHT; y++)
        {
            state.grid[x][y] = CELL_CLEAR;
        }
    }
}

/**
 * @brief Draw a single character to the screen
 * 
 * @param character - the character to draw
 * @param position - where to draw the character
 */
void draw_character(const char character, position position)
{
    lcd.setCursor(position.x, position.y);
    lcd.write(character);
    state.grid[position.x][position.y] = byte(character);
}

/**
 * @brief Get the state of the LCD screen
 * 
 * @return lcd_state - the state of the screen
 */
lcd_state get_current_lcd_state()
{
    return state;
}

/**
 * @brief Draw a number in the 2048 sequence
 * 
 * @param number - the number to draw - a power of 2 from 1 to 2048
 * @param position - where to draw the number
 */
void draw_number(int number, position position)
{
    switch(number)
    {
        case 1:
            return draw_character('1', position);
        case 2:
            return draw_character('2', position);
        case 4:
            return draw_character('4', position);
        case 8:
            return draw_character('8', position);
        case 16:
            return draw_character(NUM_16, position);
        case 32:
            return draw_character(NUM_32, position);
        case 64:
            return draw_character(NUM_64, position);
        case 128:
            return draw_character(NUM_128, position);
        case 256:
            return draw_character(NUM_256, position);
        case 512:
            return draw_character(NUM_512, position);
        case 1024:
            return draw_character(NUM_1024, position);
        default:
            Serial.println("Unknown number"); Serial.println(number);
    }
}

/**
 * @brief Draw bytes starting at the given position
 *        Similar to draw_text but not stopped by a null byte
 * 
 * @param text - the text to draw
 * @param start_position - where to start drawing
 * @param length - how many bytes to read
 */
void draw_bytes(const char *text, position start_position, size_t length)
{
    position new_position = start_position;
    for (unsigned int i = 0; i < length; i++)
    {
        draw_character(text[i], new_position);
        new_position.x = new_position.x + 1;
    }
}

/**
 * @brief Draw text starting at the given position
 * 
 * @param text - the text to draw
 * @param start_position - where to start drawing
 */
void draw_text(const char *text, position start_position)
{
    draw_bytes(text, start_position, strlen(text));
}