#pragma once

#include <Input.hpp>
#include "game_state.h"

void init_play_scene(GameState *game_state);
void render_play_scene(GameState *game_state);
void update_play_scene(GameState *game_state, button button_pressed);
