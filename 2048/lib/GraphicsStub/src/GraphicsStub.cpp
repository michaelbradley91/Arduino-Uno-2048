#include <CException.h>
#include <GraphicsFake.hpp>
#include <unity.h>
#include <CMock.h>

/**
 * @brief The current state based on what the user has been running
 */
static lcd_state screen_state = {};

/**
 * @brief Stub functions to mimic the LCD screen follow
 */
static void reset_screen_stub(int num_calls)
{
    for (int x = 0; x < LCD_WIDTH; x++)
    {
        for (int y = 0; y < LCD_HEIGHT; y++)
        {
            screen_state.grid[x][y] = CELL_CLEAR;
        }
    }
}

static void draw_character_stub(char character, position *pos, int num_calls)
{
    screen_state.grid[pos->x][pos->y] = character;
}

static void draw_number_stub(int number, position *pos, int num_calls)
{
    char number_character = CELL_CLEAR;
    switch(number)
    {
        case 1:
            number_character = '1';
            break;
        case 2:
            number_character = '2';
            break;
        case 4:
            number_character = '4';
            break;
        case 8:
            number_character = '8';
            break;
        case 16:
            number_character = NUM_16;
            break;
        case 32:
            number_character = NUM_32;
            break;
        case 64:
            number_character = NUM_64;
            break;
        case 128:
            number_character = NUM_128;
            break;
        case 256:
            number_character = NUM_256;
            break;
        case 512:
            number_character = NUM_512;
            break;
        case 1024:
            number_character = NUM_1024;
            break;
        default:
            number_character = CELL_CLEAR;
    }
    draw_character(number_character, pos);
}

static void draw_bytes_stub(const char *text, position *start_position, size_t length, int num_calls)
{
    position new_position = *start_position;
    for (unsigned int i = 0; i < length; i++)
    {
        draw_character(text[i], &new_position);
        new_position.x = new_position.x + 1;
    }
}

static void draw_text_stub(const char *text, position *start_position, int num_calls)
{
    draw_bytes(text, start_position, strlen(text));
}

lcd_state get_current_lcd_state_stub(int num_calls)
{
    return screen_state;
}

/**
 * @brief Initialise stub callbacks for the graphics library.
 *        These stubs just record what would have been shown on screen.
 */
void init_graphics_stub(void)
{
    reset_screen_Stub(reset_screen_stub);
    draw_character_Stub(draw_character_stub);
    draw_number_Stub(draw_number_stub);
    draw_bytes_Stub(draw_bytes_stub);
    draw_text_Stub(draw_text_stub);
    get_current_lcd_state_Stub(get_current_lcd_state_stub);
}
