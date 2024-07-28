
#include <unity.h>
#include <Graphics.hpp>
#include <Arduino.h>
#include <pins.h>

void setUp(void) {
    reset_screen();
}

void tearDown(void) {
    /* Give the LCD screen a breather */
    delay(200);
}

/**
 * @brief test that when we reset the screen, all displayed characters are gone
 * 
 */
void test_reset_screen_does_clear_the_screen()
{
    /* Write some stuff on the screen first */
    for (int x = 0; x < LCD_WIDTH; x++)
    {
        for (int y = 0; y < LCD_HEIGHT; y++)
        {
            position pos = {x: x, y: y};
            draw_character(((unsigned char)('A')) + ((unsigned char)(x + y * LCD_WIDTH)), &pos);
        }
    }
    delay(200);
    reset_screen();
    delay(200);
    lcd_state display = get_current_lcd_state();
    for (int x = 0; x < LCD_WIDTH; x++)
    {
        for (int y = 0; y < LCD_HEIGHT; y++)
        {
            TEST_ASSERT_EQUAL_UINT8(CELL_CLEAR, display.grid[x][y]);
        }
    }
}