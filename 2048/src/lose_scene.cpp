#include <Graphics.hpp>
#include <util.h>
#include <lose_scene.h>

const char *lost_characters[] = {
    "[1024]",
    "[512] ",
    "[256] ",
    "[128] ",
    " [64] ",
    " [32] ",
    " [16] ",
    " [8]  ",
    " [4]  ",
    " [2]  ",
    " [1]  "
};

static const char* get_lose_score(GameState *game_state)
{
    int max_number = 2;
    for (int x = 0; x < 4; x++)
    {
        for (int y = 0; y < 4; y++)
        {
            if (game_state->grid.cells[x][y] > max_number)
            {
                max_number = game_state->grid.cells[x][y];
            }
        }
    }
    switch(max_number)
    {
        case 2:
            return lost_characters[9];
        case 4:
            return lost_characters[8];
        case 8:
            return lost_characters[7];
        case 16:
            return lost_characters[6];
        case 32:
            return lost_characters[5];
        case 64:
            return lost_characters[4];
        case 128:
            return lost_characters[3];
        case 256:
            return lost_characters[2];
        case 512:
            return lost_characters[1];
        case 1024:
            return lost_characters[0];
        default:
            return lost_characters[10];
    }
}

/**
 * @brief Initialise this scene
 * 
 * @param game_state - the current state of the game
 */
void init_lose_scene(GameState *game_state)
{
    use_lose_characters();
    const char *lost_score = get_lose_score(game_state);
    position pos = {x: 0, y: 0};
    draw_bytes(" " SAD_TOP_STR "  ", &pos, 5);
    pos = {x: 5, y: 0};
    draw_text(lost_score, &pos);
    pos = {x: 11, y: 0};
    draw_bytes("  " SAD_TOP_STR " ", &pos, 5);
    pos = {x: 0, y: 1};
    draw_text(" " SAD_BOTTOM_STR " You Lost " SAD_BOTTOM_STR " ", &pos);
}

/**
 * @brief Render this scene
 * 
 * @param game_state - the current state of the game
 */
void render_lose_scene(GameState *game_state)
{
}

/**
 * @brief Update this scene with the given button press
 * 
 * @param game_state - the current state of the game
 * @param button_pressed - the button that was just pressed
 */
void update_lose_scene(GameState *game_state, button button_pressed)
{
    if (button_pressed == BUTTON_BACK)
    {
        update_scene(game_state, SCENE_START);
    }
}