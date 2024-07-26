#include <Graphics.hpp>
#include <random.h>
#include <util.h>
#include <play_scene.h>

/**
 * @brief Initialise this scene
 * 
 * @param game_state - the current state of the game
 */
void init_play_scene(GameState *game_state)
{
    use_play_characters();
    init_random();

    /* Reset the grid in case */
    memset(&game_state->grid, 0, sizeof(game_state->grid));

    /* Draw the surrounding boxes */
    draw_character(LEFT_BORDER, {x : 1, y : 0});
    draw_character(LEFT_BORDER, {x : 1, y : 1});
    draw_character(RIGHT_BORDER, {x : 6, y : 0});
    draw_character(RIGHT_BORDER, {x : 6, y : 1});
    draw_character(LEFT_BORDER, {x : 9, y : 0});
    draw_character(LEFT_BORDER, {x : 9, y : 1});
    draw_character(RIGHT_BORDER, {x : 14, y : 0});
    draw_character(RIGHT_BORDER, {x : 14, y : 1});
    draw_character(RIGHT_ARROW, {x : 7, y : 1});
    draw_character(RIGHT_ARROW, {x : 8, y : 0});

    /* Start by adding two random numbers */
    add_random_number_to_grid(&game_state->grid);
    add_random_number_to_grid(&game_state->grid);
}

/**
 * @brief Get the graphical position for the given cell coordinates
 * 
 * @param x - the x position of the cell
 * @param y - the y position of the cell
 * @return position - the position of the cell on the LCD screen
 */
static position get_position_for_cell(int x, int y)
{
    /* Top half */
    if (y < 2)
    {
        return {x: 2 + x, y: y};
    }
    /* Bottom half */
    return {x: 10 + x, y: y - 2};
}

/**
 * @brief Render this scene
 * 
 * @param game_state - the current state of the game
 */
void render_play_scene(GameState *game_state)
{
    /* Only render the cells that need changing */
    lcd_state screen_state = get_current_lcd_state();
    for (int x = 0; x < 4; x++)
    {
        for (int y = 0; y < 4; y++)
        {
            /* Get the character currently on the screen */
            position graphics_position = get_position_for_cell(x, y);
            char screen_character = screen_state.grid[graphics_position.x][graphics_position.y];

            /* Does it differ to what should be drawn? */
            int cell_value = game_state->grid.cells[x][y];
            if (get_number_character(cell_value) != screen_character)
            {
                draw_number(cell_value, graphics_position);
            }
        }
    }
}

/**
 * @brief Update this scene with the given button press
 * 
 * @param game_state - the current state of the game
 * @param button_pressed - the button that was just pressed
 */
void update_play_scene(GameState *game_state, button button_pressed)
{
    
}