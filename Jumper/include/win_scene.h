#pragma once

#include <Input.hpp>
#include "game_state.h"

void init_win_scene(GameState *game_state);
void render_win_scene(GameState *game_state);
void update_win_scene(GameState *game_state, button button_pressed);
