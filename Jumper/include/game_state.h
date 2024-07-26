#pragma once

/**
 * @brief The scenes of the game, or in other words which menu are we looking at?
 */
typedef enum Scene
{
    SCENE_START = 0,
    SCENE_WIN,
    SCENE_LOSE,
    SCENE_PLAY,
};

/**
 * @brief The grid holding the numbers in 2048
 */
typedef struct
{
    int values[4][4];
} Grid;

/**
 * @brief The overall game state, used to determine how to draw the game
 */
typedef struct
{
    Scene scene;
    Grid grid;
} GameState;
