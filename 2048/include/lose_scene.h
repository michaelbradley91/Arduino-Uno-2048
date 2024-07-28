#pragma once

#include <Input.hpp>
#include "game_state.h"

void init_lose_scene(GameState *game_state);
void render_lose_scene(GameState *game_state);
void update_lose_scene(GameState *game_state, button button_pressed);
