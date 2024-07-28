#include <Graphics.hpp>
#include <util.h>
#include <win_scene.h>

/**
 * @brief Initialise this scene
 * 
 * @param game_state - the current state of the game
 */
void init_win_scene(GameState *game_state)
{
    use_win_characters();
    position pos = {x: 0, y: 0};
    draw_bytes(" " TROPHY_TOP_STR "  [2048]  " TROPHY_TOP_STR " ", &pos, 16);
    pos = {x: 0, y: 1};
    draw_text(" " TROPHY_BOTTOM_STR " You Win! " TROPHY_BOTTOM_STR " ", &pos);
}

/**
 * @brief Render this scene
 * 
 * @param game_state - the current state of the game
 */
void render_win_scene(GameState *game_state)
{
}

/**
 * @brief Update this scene with the given button press
 * 
 * @param game_state - the current state of the game
 * @param button_pressed - the button that was just pressed
 */
void update_win_scene(GameState *game_state, button button_pressed)
{
    if (button_pressed == BUTTON_BACK)
    {
        update_scene(game_state, SCENE_START);
    }
}
