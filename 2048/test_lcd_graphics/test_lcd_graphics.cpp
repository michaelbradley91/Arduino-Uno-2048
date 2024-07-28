
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
 * @brief Convenience function to draw a number at a position
 * 
 * @param number - the number to draw
 * @param pos - the position
 */
static void draw_number_at(int number, position pos)
{
    draw_number(number, &pos);
}

/**
 * @brief Convenience function to draw text at a position
 * 
 * @param text - the text to draw
 * @param pos - the position
 */
static void draw_text_at(const char *text, position pos)
{
    draw_text(text, &pos);
}

/**
 * @brief Convenience function to draw bytes at a position
 * 
 * @param text - the bytes to draw
 * @param pos - the position
 * @param length - the number of bytes
 */
static void draw_bytes_at(const char *bytes, position pos, size_t length)
{
    draw_bytes(bytes, &pos, length);
}

/**
 * @brief test that when we reset the screen, all displayed characters are gone
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

/**
 * @brief Test that when we draw a good number, the right symbol is shown
 */
void test_draw_number_given_valid_number_draws_the_correct_number()
{
    /* Draw all the numbers first */
    draw_number_at(2, {x: 0, y: 0});
    draw_number_at(4, {x: 1, y: 0});
    draw_number_at(8, {x: 2, y: 0});
    draw_number_at(16, {x: 3, y: 0});
    draw_number_at(32, {x: 4, y: 0});
    draw_number_at(64, {x: 5, y: 0});
    draw_number_at(128, {x: 6, y: 0});
    draw_number_at(256, {x: 7, y: 0});
    draw_number_at(512, {x: 8, y: 0});
    draw_number_at(1024, {x: 9, y: 0});

    delay(200);
    lcd_state state = get_current_lcd_state();

    /* Check all the numbers have appeared */
    TEST_ASSERT_EQUAL_CHAR('2', state.grid[0][0]);
    TEST_ASSERT_EQUAL_CHAR('4', state.grid[1][0]);
    TEST_ASSERT_EQUAL_CHAR('8', state.grid[2][0]);
    TEST_ASSERT_EQUAL_CHAR(NUM_16, state.grid[3][0]);
    TEST_ASSERT_EQUAL_CHAR(NUM_32, state.grid[4][0]);
    TEST_ASSERT_EQUAL_CHAR(NUM_64, state.grid[5][0]);
    TEST_ASSERT_EQUAL_CHAR(NUM_128, state.grid[6][0]);
    TEST_ASSERT_EQUAL_CHAR(NUM_256, state.grid[7][0]);
    TEST_ASSERT_EQUAL_CHAR(NUM_512, state.grid[8][0]);
    TEST_ASSERT_EQUAL_CHAR(NUM_1024, state.grid[9][0]);
}

/**
 * @brief Test that if we try to draw an invalid number, the cell is cleared 
 */
void test_draw_number_with_invalid_number_clears_cell()
{
    /* Draw a valid number so can be sure it was cleared */
    draw_number_at(2, {x: 0, y: 0});
    delay(200);

    /* Check the valid number appeared */
    lcd_state state = get_current_lcd_state();
    TEST_ASSERT_EQUAL_CHAR('2', state.grid[0][0]);

    /* Draw the invalid number */
    draw_number_at(3, {x: 0, y: 0});
    delay(200);

    /* Check the number was cleared */
    state = get_current_lcd_state();
    TEST_ASSERT_EQUAL_CHAR(CELL_CLEAR, state.grid[0][0]);
}

/**
 * @brief Test that when valid text is drawn (fits on the screen), it appears
 */
void test_draw_text_with_valid_text_works()
{
    /* Draw the text */
    draw_text_at("Hello", {x: 2, y: 1});
    delay(200);

    /* Verify the text appeared */
    lcd_state state = get_current_lcd_state();
    TEST_ASSERT_EQUAL_CHAR('H', state.grid[2][1]);
    TEST_ASSERT_EQUAL_CHAR('e', state.grid[3][1]);
    TEST_ASSERT_EQUAL_CHAR('l', state.grid[4][1]);
    TEST_ASSERT_EQUAL_CHAR('l', state.grid[5][1]);
    TEST_ASSERT_EQUAL_CHAR('o', state.grid[6][1]);
}

/**
 * @brief When we ask the display to draw text that will not fit, it should be truncated
 */
void test_draw_text_with_text_too_long_truncates_text()
{
    /* Draw the text */
    draw_text_at("Hello", {x: LCD_WIDTH - 2, y: 0});
    delay(200);

    /* Verify the text */
    lcd_state state = get_current_lcd_state();
    TEST_ASSERT_EQUAL_CHAR('H', state.grid[LCD_WIDTH - 2][0]);
    TEST_ASSERT_EQUAL_CHAR('e', state.grid[LCD_WIDTH - 1][0]);
}

/**
 * @brief When we draw bytes, it will draw the "NULL" byte correctly
 */
void test_draw_bytes_with_valid_bytes_handles_null_correctly()
{
    /* Check our assumptions */
    use_win_characters();
    TEST_ASSERT_EQUAL_CHAR('\x00', TROPHY_TOP_LEFT);

    /* Draw our own byte sequence */
    char bytes[] = {'W', 'o', 'w', TROPHY_TOP_LEFT, '!'};
    draw_bytes_at(bytes, {x: 0, y: 0}, sizeof(bytes));
    delay(200);

    /* Verify all bytes were drawn */
    lcd_state state = get_current_lcd_state();
    TEST_ASSERT_EQUAL_CHAR('W', state.grid[0][0]);
    TEST_ASSERT_EQUAL_CHAR('o', state.grid[1][0]);
    TEST_ASSERT_EQUAL_CHAR('w', state.grid[2][0]);
    TEST_ASSERT_EQUAL_CHAR(TROPHY_TOP_LEFT, state.grid[3][0]);
    TEST_ASSERT_EQUAL_CHAR('!', state.grid[4][0]);
}

/**
 * @brief Test that when we draw bytes beyond the size of the LCD screen, they are truncated
 */
void test_draw_bytes_with_bytes_too_long_truncates_bytes()
{
    /* Draw our own byte sequence */
    use_win_characters();
    char bytes[] = {'W', 'o', 'w', TROPHY_TOP_LEFT, '!', 'W', 'o', 'o'};
    draw_bytes_at(bytes, {x: LCD_WIDTH - 4, y: 0}, sizeof(bytes));
    delay(200);

    /* Verify all bytes were drawn */
    lcd_state state = get_current_lcd_state();
    TEST_ASSERT_EQUAL_CHAR('W', state.grid[LCD_WIDTH - 4][0]);
    TEST_ASSERT_EQUAL_CHAR('o', state.grid[LCD_WIDTH - 3][0]);
    TEST_ASSERT_EQUAL_CHAR('w', state.grid[LCD_WIDTH - 2][0]);
    TEST_ASSERT_EQUAL_CHAR(TROPHY_TOP_LEFT, state.grid[LCD_WIDTH - 1][0]);
}
