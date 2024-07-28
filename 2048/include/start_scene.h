#pragma once

#include <Input.hpp>
#include "game_state.h"

void init_start_scene(GameState *game_state);
void render_start_scene(GameState *game_state);
void update_start_scene(GameState *game_state, button button_pressed);
