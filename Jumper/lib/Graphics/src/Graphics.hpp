#pragma once

/**
 * @brief Assume size of LCD board
 * 
 */
#define LCD_WIDTH 16
#define LCD_HEIGHT 2

/**
 * @brief Useful constants
 */
#define CELL_CLEAR '\xfe'
#define CELL_BLOCK '\xff'
#define NUM_1024 '\xff'

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

/**
 * @brief Where to draw something on screen
 */
typedef struct
{
    int x;
    int y;
} position;

/**
 * @brief The range of symbols that can be drawn with the graphics library
 */
typedef enum
{
    LEFT_BORDER = 0,
    RIGHT_BORDER = 1,
    NUM_16 = 2,
    NUM_32 = 3,
    NUM_64 = 4,
    NUM_128 = 5,
    NUM_256 = 6,
    NUM_512 = 7
} SYMBOL;
