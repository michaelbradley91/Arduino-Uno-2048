
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
byte sad_top_left[] = { B00000, B00000, B00000, B00011, B00100, B01000, B10010, B10000 };
byte sad_top_right[] = { B00000, B00000, B00000, B11000, B00100, B00010, B01001, B00001 };
byte sad_bottom_left[] = { B10000, B10001, B01010, B00100, B00011, B00000, B00000, B00000 };
byte sad_bottom_right[] = { B00001, B10001, B01010, B00100, B11000, B00000, B00000, B00000 };

static int has_initialised = 0;

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
    Serial.println("Init graphics");

    if (has_initialised) return;
    lcd = LiquidCrystal(pins.register_select, pins.enable, pins.d4, pins.d5, pins.d6, pins.d7);
    lcd.begin(LCD_WIDTH, LCD_HEIGHT);
    reset_screen();
    has_initialised = 1;
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
 * @brief Use the "lose" character set to express that tragic loss!
 */
void use_lose_characters(void)
{
    lcd.createChar(SAD_TOP_LEFT, sad_top_left);
    lcd.createChar(SAD_TOP_RIGHT, sad_top_right);
    lcd.createChar(SAD_BOTTOM_LEFT, sad_bottom_left);
    lcd.createChar(SAD_BOTTOM_RIGHT, sad_bottom_right);
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
void draw_character(const char character, position *position)
{
    /* Refuse to draw if outside the bounds of the LCD screen */
    if (position->x < 0 || position->x >= LCD_WIDTH || position->y < 0 || position->y >= LCD_HEIGHT)
    {
        return;
    }
    lcd.setCursor(position->x, position->y);
    lcd.write(character);
    state.grid[position->x][position->y] = byte(character);
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
 * @brief Get the character corresponding to the given number
 * 
 * @param number - the numerical value
 * @return char - the character that would be rendered for it
 */
char get_number_character(int number)
{
    switch(number)
    {
        case 1:
            return '1';
        case 2:
            return '2';
        case 4:
            return '4';
        case 8:
            return '8';
        case 16:
            return NUM_16;
        case 32:
            return NUM_32;
        case 64:
            return NUM_64;
        case 128:
            return NUM_128;
        case 256:
            return NUM_256;
        case 512:
            return NUM_512;
        case 1024:
            return NUM_1024;
        default:
            return CELL_CLEAR;
    }
}

/**
 * @brief Draw a number in the 2048 sequence
 * 
 * @param number - the number to draw - a power of 2 from 1 to 2048
 * @param position - where to draw the number
 */
void draw_number(int number, position *position)
{
    draw_character(get_number_character(number), position);
}

/**
 * @brief Draw bytes starting at the given position
 *        Similar to draw_text but not stopped by a null byte
 * 
 * @param text - the text to draw
 * @param start_position - where to start drawing
 * @param length - how many bytes to read
 */
void draw_bytes(const char *text, position *start_position, size_t length)
{
    position new_position = *start_position;
    for (unsigned int i = 0; i < length; i++)
    {
        draw_character(text[i], &new_position);
        new_position.x = new_position.x + 1;
    }
}

/**
 * @brief Draw text starting at the given position
 * 
 * @param text - the text to draw
 * @param start_position - where to start drawing
 */
void draw_text(const char *text, position *start_position)
{
    draw_bytes(text, start_position, strlen(text));
}