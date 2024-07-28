#pragma once

#include <Input.hpp>

/**
 * @brief The scenes of the game, or in other words which menu are we looking at?
 */
typedef enum
{
    SCENE_START = 0,
    SCENE_WIN,
    SCENE_LOSE,
    SCENE_PLAY,
    SCENE_NONE = -1,
} Scene;

/**
 * @brief The grid holding the numbers in 2048. A value of zero means blank
 */
typedef struct
{
    int cells[4][4];
} Grid;

typedef struct GameState_s GameState;
typedef void (*SceneInit)(GameState*);
typedef void (*SceneRenderer)(GameState*);
typedef void (*SceneUpdater)(GameState*, button);

/**
 * @brief The overall game state, used to determine how to draw the game
 */
struct GameState_s
{
    Scene scene;
    SceneInit init;
    SceneRenderer renderer;
    SceneUpdater updater;
    Grid grid;
};
