#include <string.h>
#include <game_state.h>
#include <util.h>

/**
 * @brief Start a brand new game
 */
void reset_game_state(GameState *game_state)
{
    memset(game_state, 0, sizeof(GameState));
    game_state->scene = SCENE_START;
}
