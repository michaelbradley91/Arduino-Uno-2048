#include <Graphics.hpp>
#include <util.h>
#include <start_scene.h>

/**
 * @brief Initialise this scene
 * 
 * @param game_state - the current state of the game
 */
void init_start_scene(GameState *game_state)
{
    /* Draw the welcome message */
    
    draw_text("Let's Play 2048!", {x: 0, y: 0});
    draw_text(NUM_1024_STR "+" NUM_1024_STR "=2048 <Start>", {x: 0, y: 1});
}

/**
 * @brief Render this scene
 * 
 * @param game_state - the current state of the game
 */
void render_start_scene(GameState *game_state)
{
    /* Nothing changes on the start screen yet... */
    return;
}

/**
 * @brief Update this scene with the given button press
 * 
 * @param game_state - the current state of the game
 * @param button_pressed - the button that was just pressed
 */
void update_start_scene(GameState *game_state, button button_pressed)
{
    update_scene(game_state, SCENE_PLAY);
}