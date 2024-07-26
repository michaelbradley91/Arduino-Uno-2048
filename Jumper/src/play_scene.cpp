#include <Graphics.hpp>
#include <Arduino.h>
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
 * @brief Slide all cells as far as they will go
 *        without combining anything
 * 
 * @param grid - the grid to modify
 * @param delta_x - the slide direction in x
 * @param delta_y - the slide direction in y
 */
static void slide(Grid *grid, int delta_x, int delta_y)
{
    /*
     * Calculate the boundaries of cells
     * and their neighbours for sliding
     */
    int small_x = max(0, -delta_x);
    int small_y = max(0, -delta_y);
    int big_x = min(3, 3 - delta_x);
    int big_y = min(3, 3 - delta_y);

    /*
     * We can only slide cells so many times...
     * This is really inefficient but works
     */
    int has_changed = 0;
    while(1)
    {
        for (int x = small_x; x <= big_x; x++)
        {
            for (int y = small_y; y <= big_y; y++)
            {
                /* Is our neighbour free? */
                if (grid->cells[x][y] > 0 && grid->cells[x + delta_x][y + delta_y] == 0)
                {
                    grid->cells[x + delta_x][y + delta_y] = grid->cells[x][y];
                    grid->cells[x][y] = 0;
                    has_changed = 1;
                }
            }
        }
        if (!has_changed)
        {
            return;
        }
        has_changed = 0;
    }
}

/**
 * @brief Combine any pair of cells on the grid in the direction
 *        of the slide. This always combines into the slide direction
 * 
 * @param grid - the grid to modify
 * @param delta_x - the slide direction in x
 * @param delta_y - the slide direction in y
 */
static void combine(Grid *grid, int delta_x, int delta_y)
{
    /*
     * This could definitely be smarter, but we just brute force
     * the slide directions
     */
    if (delta_x > 0)
    {
        for (int x = 2; x >= 0; x--)
        {
            for (int y = 0; y < 4; y++)
            {
                if (grid->cells[x][y] == grid->cells[x + delta_x][y + delta_y])
                {
                    grid->cells[x + delta_x][y + delta_y] *= 2;
                    grid->cells[x][y] = 0;
                }
            }
        }
    }
    else if (delta_x < 0)
    {
        for (int x = 1; x < 4; x++)
        {
            for (int y = 0; y < 4; y++)
            {
                if (grid->cells[x][y] == grid->cells[x + delta_x][y + delta_y])
                {
                    grid->cells[x + delta_x][y + delta_y] *= 2;
                    grid->cells[x][y] = 0;
                }
            }
        }
    }
    else if (delta_y > 0)
    {
        for (int x = 0; x < 4; x++)
        {
            for (int y = 2; y >= 0; y--)
            {
                if (grid->cells[x][y] == grid->cells[x + delta_x][y + delta_y])
                {
                    grid->cells[x + delta_x][y + delta_y] *= 2;
                    grid->cells[x][y] = 0;
                }
            }
        }
    }
    else  /* delta_y < 0 */
    {
        for (int x = 0; x < 4; x++)
        {
            for (int y = 1; y < 4; y++)
            {
                if (grid->cells[x][y] == grid->cells[x + delta_x][y + delta_y])
                {
                    grid->cells[x + delta_x][y + delta_y] *= 2;
                    grid->cells[x][y] = 0;
                }
            }
        }
    }
}

/**
 * @brief Check if the current grid position is lost
 * 
 * The game is lost when there is no way to slide or combine numbers.
 * 
 * @param grid - the grid to check
 * @return - 1 if the game is lost, and 0 otherwise.
 */
int is_lost(Grid *grid)
{
    for (int x = 0; x < 4; x++)
    {
        for (int y = 0; y < 4; y++)
        {
            /* Any free cell means we can slide */
            if (grid->cells[x][y] == 0)
            {
                return 0;
            }
            /* Can we combine this with anything? */
            if (x - 1 >= 0 && grid->cells[x - 1][y] == grid->cells[x][y])
            {
                return 0;
            }
            if (x + 1 < 4 && grid->cells[x + 1][y] == grid->cells[x][y])
            {
                return 0;
            }
            if (y - 1 >= 0 && grid->cells[x][y - 1] == grid->cells[x][y])
            {
                return 0;
            }
            if (y + 1 < 4 && grid->cells[x][y + 1] == grid->cells[x][y])
            {
                return 0;
            }
        }
    }
    return 1;
}

/**
 * @brief Check if the grid is won - does it have a 2048?
 * 
 * @param grid - the grid to check
 * @return - 1 if the game is won, and 0 otherwise
 */
int is_won(Grid *grid)
{
    for (int x = 0; x < 4; x++)
    {
        for (int y = 0; y < 4; y++)
        {
            if (grid->cells[x][y] == 2048)
            {
                return 1;
            }
        }
    }
    return 0;
}

/**
 * @brief Update this scene with the given button press
 * 
 * @param game_state - the current state of the game
 * @param button_pressed - the button that was just pressed
 */
void update_play_scene(GameState *game_state, button button_pressed)
{
    /* 
     * To the let the player realise they have lost, we let them see
     * the final position
     */
    if (is_lost(&game_state->grid))
    {
        update_scene(game_state, SCENE_LOSE);
        return;
    }

    int delta_x = 0;
    int delta_y = 0;
    switch(button_pressed)
    {
        case BUTTON_LEFT:
            delta_x = -1;
            break;
        case BUTTON_RIGHT:
            delta_x = 1;
            break;
        case BUTTON_DOWN:
            delta_y = 1;
            break;
        case BUTTON_UP:
            delta_y = -1;
            break;
        case BUTTON_BACK:
            update_scene(game_state, SCENE_START);
            return;
        default:
            return;
    }

    /*
     * Update the grid by sliding and combining numbers.
     * Note that combining is only done once.
     */
    Grid grid_copy = game_state->grid;
    slide(&game_state->grid, delta_x, delta_y);
    combine(&game_state->grid, delta_x, delta_y);
    slide(&game_state->grid, delta_x, delta_y);

    /* Did anything change? If not, the move is ignored */
    if (memcmp(&grid_copy, &game_state->grid, sizeof(Grid)) == 0) return;

    /* Add a new number if possible */
    add_random_number_to_grid(&game_state->grid);

    /* 
     * Check if the player won (you can reach an unmovable position
     * after winning)
     */
    if (is_won(&game_state->grid))
    {
        update_scene(game_state, SCENE_WIN);
        return;
    }
}