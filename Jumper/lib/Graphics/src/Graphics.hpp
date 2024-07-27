#pragma once

#include <Arduino.h>
#include <position.h>

/**
 * @brief Assume size of LCD board
 * 
 */
#define LCD_WIDTH 16
#define LCD_HEIGHT 2

/**
 * @brief Useful constants
 */
#define LEFT_BORDER         '\x00'
#define RIGHT_BORDER        '\x01'
#define NUM_16              '\x02'
#define NUM_32              '\x03'
#define NUM_64              '\x04'
#define NUM_128             '\x05'
#define NUM_256             '\x06'
#define NUM_512             '\x07'
#define TROPHY_TOP_LEFT     '\x00'
#define TROPHY_TOP_RIGHT    '\x01'
#define TROPHY_BOTTOM_LEFT  '\x02'
#define TROPHY_BOTTOM_RIGHT '\x03'
#define SAD_TOP_LEFT        '\x00'
#define SAD_TOP_RIGHT       '\x01'
#define SAD_BOTTOM_LEFT     '\x02'
#define SAD_BOTTOM_RIGHT    '\x03'
#define RIGHT_ARROW         '\x7e'
#define CELL_CLEAR          '\xfe'
#define CELL_BLOCK          '\xff'
#define NUM_1024            '\xff'

/**
 * @brief String versions of the special characters
 */
#define LEFT_BORDER_STR         "\x00"
#define RIGHT_BORDER_STR        "\x01"
#define NUM_16_STR              "\x02"
#define NUM_32_STR              "\x03"
#define NUM_64_STR              "\x04"
#define NUM_128_STR             "\x05"
#define NUM_256_STR             "\x06"
#define NUM_512_STR             "\x07"
#define TROPHY_TOP_LEFT_STR     "\x00"
#define TROPHY_TOP_RIGHT_STR    "\x01"
#define TROPHY_BOTTOM_LEFT_STR  "\x02"
#define TROPHY_BOTTOM_RIGHT_STR "\x03"
#define SAD_TOP_LEFT_STR        "\x00"
#define SAD_TOP_RIGHT_STR       "\x01"
#define SAD_BOTTOM_LEFT_STR     "\x02"
#define SAD_BOTTOM_RIGHT_STR    "\x03"
#define RIGHT_ARROW_STR         "\x7e"
#define CELL_CLEAR_STR          "\xfe"
#define CELL_BLOCK_STR          "\xff"
#define NUM_1024_STR            "\xff"
#define TROPHY_TOP_STR          TROPHY_TOP_LEFT_STR TROPHY_TOP_RIGHT_STR
#define TROPHY_BOTTOM_STR       TROPHY_BOTTOM_LEFT_STR TROPHY_BOTTOM_RIGHT_STR
#define SAD_TOP_STR             SAD_TOP_LEFT_STR SAD_TOP_RIGHT_STR
#define SAD_BOTTOM_STR          SAD_BOTTOM_LEFT_STR SAD_BOTTOM_RIGHT_STR

/**
 * @brief Type for passing the pin information to the graphics library
 */
typedef struct
{
    int register_select;
    int enable;
    int d4;
    int d5;
    int d6;
    int d7;
} lcd_pins;

/**
 * @brief The type used to hold the LCD's current state
 */
typedef struct
{
    byte grid[LCD_WIDTH][LCD_HEIGHT];
} lcd_state;

void init_graphics(lcd_pins pins);
void turn_off_screen(void);
void turn_on_screen(void);
void reset_screen(void);
void use_play_characters(void);
void use_win_characters(void);
void use_lose_characters(void);
void draw_character(const char character, position *position);
char get_number_character(int number);
void draw_number(int number, position *position);
void draw_bytes(const char *text, position *start_position, size_t length);
void draw_text(const char *text, position *start_position);

lcd_state get_current_lcd_state();
