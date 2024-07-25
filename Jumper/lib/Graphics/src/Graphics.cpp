
#include "Graphics.hpp"
#include <Arduino.h>
#include <LiquidCrystal.h>


/**
 * @brief Custom characters
 */
byte left_border[]  = { B00110, B00110, B00110, B00110, B00110, B00110, B00110, B00110 };
byte right_border[] = { B01100, B01100, B01100, B01100, B01100, B01100, B01100, B01100 };
byte num_16[]       = { B11111, B10001, B10001, B10001, B10001, B10001, B10001, B11111 };
byte num_32[]       = { B11111, B10001, B10001, B10001, B10001, B10001, B11111, B11111 };
byte num_64[]       = { B11111, B10001, B10001, B10001, B10001, B11111, B11111, B11111 };
byte num_128[]      = { B11111, B10001, B10001, B10001, B11111, B11111, B11111, B11111 };
byte num_256[]      = { B11111, B10001, B10001, B11111, B11111, B11111, B11111, B11111 };
byte num_512[]      = { B11111, B10001, B11111, B11111, B11111, B11111, B11111, B11111 };

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
    lcd.createChar(LEFT_BORDER, left_border);
    lcd.createChar(RIGHT_BORDER, right_border);
    lcd.createChar(NUM_16, num_16);
    lcd.createChar(NUM_32, num_32);
    lcd.createChar(NUM_64, num_64);
    lcd.createChar(NUM_128, num_128);
    lcd.createChar(NUM_256, num_256);
    lcd.createChar(NUM_512, num_512);
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
 * @brief Draw text starting at the given position
 * 
 * @param text - the text to draw
 * @param start_position - where to start drawing
 */
void draw_text(const char *text, position start_position)
{
    position new_position = start_position;
    for (unsigned int i = 0; i < strlen(text); i++)
    {
        Serial.println("Drawing character at position: ");
        Serial.print(new_position.x);
        Serial.print(", ");
        Serial.print(new_position.y);
        Serial.print(", ");
        Serial.print(byte(text[i]));
        Serial.println("");
        draw_character(text[i], new_position);
        new_position.x = new_position.x + 1;
    }
}
