#include <string.h>
#include <game_state.h>
#include <util.h>
#include <lose_scene.h>
#include <win_scene.h>
#include <start_scene.h>
#include <play_scene.h>
#include <Graphics.hpp>

/**
 * @brief Change the scene of the game
 * 
 * @param game_state - the current game state
 * @param new_scene - the scene to change to. If this is the same as the current scene,
 *                    nothing happens
 */
void update_scene(GameState *game_state, Scene new_scene)
{
    /* Do nothing if we are already on the given scene */
    if (new_scene == game_state->scene)
    {
        return;
    }
    game_state->scene = new_scene;

    /* Set all the function pointers */
    switch(new_scene)
    {
        case SCENE_START:
            game_state->init = init_start_scene;
            game_state->renderer = render_start_scene;
            game_state->updater = update_start_scene;
            break;
        case SCENE_PLAY:
            game_state->init = init_play_scene;
            game_state->renderer = render_play_scene;
            game_state->updater = update_play_scene;
            break;
        case SCENE_WIN:
            game_state->init = init_win_scene;
            game_state->renderer = render_win_scene;
            game_state->updater = update_win_scene;
            break;
        case SCENE_LOSE:
            game_state->init = init_lose_scene;
            game_state->renderer = render_lose_scene;
            game_state->updater = update_lose_scene;
            break;
        default:
            /* This should not be allowed to happen. If it does. Reset */
            Serial.print("Unknown scene");
            Serial.println(new_scene);
            reset_game_state(game_state);
            return;
    }
    Serial.println("Clearing screen with state change\n");

    /* Reset the LCD screen automatically */
    reset_screen();

    /* Finally, invoke the initialiser of the correct scene */
    game_state->init(game_state);
}

/**
 * @brief Start a brand new game
 */
void reset_game_state(GameState *game_state)
{
    memset(game_state, 0, sizeof(GameState));

    /* Force an update to the screen */
    game_state->scene = SCENE_NONE;
    update_scene(game_state, SCENE_START);
}

