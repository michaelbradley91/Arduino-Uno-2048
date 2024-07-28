#include <unity.h>
#include <GraphicsFake.hpp>
#include <GraphicsStub.hpp>
#include <randomFake.h>
#include <play_scene.h>
#include <unity_extensions.h>
#include <string.h>

extern position get_position_for_cell(int x, int y);

static GameState game_state = {};
static Grid *grid = &game_state.grid;

/**
 * @brief Automatically use the graphics stub to track screen changes
 */
void setUp()
{
    memset(&game_state, 0, sizeof(game_state));
    init_graphics_stub();
}

/**
 * @brief Test that the coordinate calculation for a cell is working
 * 
 */
void test_get_position_for_cell_uses_both_rectangles()
{
    TEST_ASSERT_EQUAL_POSITION(2, 0, get_position_for_cell(0, 0));
    TEST_ASSERT_EQUAL_POSITION(5, 0, get_position_for_cell(3, 0));
    TEST_ASSERT_EQUAL_POSITION(13, 1, get_position_for_cell(3, 3));
    TEST_ASSERT_EQUAL_POSITION(13, 0, get_position_for_cell(3, 2));
}

/**
 * @brief Test that the game starts with two randomly placed numbers
 */
void test_game_starts_with_two_random_numbers()
{
    /* Expect random to be initialised and used */
    use_play_characters_Expect();
    init_random_Expect();
    add_random_number_to_grid_Expect(grid);
    add_random_number_to_grid_Expect(grid);

    /* Initialise the scene */
    init_play_scene(&game_state);
}

/**
 * @brief Test that numbers can be combined when sliding
 */
void test_numbers_can_combine()
{
    /* Set up the game */
    grid->cells[0][0] = 8;
    grid->cells[1][0] = 8;

    /* Pretend to slide right */
    add_random_number_to_grid_Expect(grid);
    update_play_scene(&game_state, BUTTON_RIGHT);

    /* Check the numbers were combined */
    TEST_ASSERT_EQUAL(16, grid->cells[3][0]);
}

/**
 * @brief Test that when numbers could be combined more than once, they are only combined once
 */
void test_numbers_only_combine_once()
{
    /* Set up the game */
    grid->cells[0][0] = 8;
    grid->cells[1][0] = 8;
    grid->cells[2][0] = 8;
    grid->cells[3][0] = 8;

    /* Pretend to slide right */
    add_random_number_to_grid_Expect(grid);
    update_play_scene(&game_state, BUTTON_RIGHT);

    /* Check the numbers were combined */
    TEST_ASSERT_EQUAL(16, grid->cells[3][0]);
    TEST_ASSERT_EQUAL(16, grid->cells[2][0]);
}

/**
 * @brief Test that when three of the same number are together,
 *        they are combined at the end of the slide's direction only
 */
void test_numbers_combined_according_to_slide_direction()
{
    /* Test slide right */
    grid->cells[0][0] = 8;
    grid->cells[1][0] = 8;
    grid->cells[2][0] = 8;

    add_random_number_to_grid_Expect(grid);
    update_play_scene(&game_state, BUTTON_RIGHT);
    
    TEST_ASSERT_EQUAL(16, grid->cells[3][0]);
    TEST_ASSERT_EQUAL(8, grid->cells[2][0]);
    memset(grid, 0, sizeof(*grid));

    /* Test slide left */
    grid->cells[0][0] = 8;
    grid->cells[1][0] = 8;
    grid->cells[2][0] = 8;

    add_random_number_to_grid_Expect(grid);
    update_play_scene(&game_state, BUTTON_LEFT);
    
    TEST_ASSERT_EQUAL(16, grid->cells[0][0]);
    TEST_ASSERT_EQUAL(8, grid->cells[1][0]);
    memset(grid, 0, sizeof(*grid));

    /* Test slide up */
    grid->cells[0][0] = 8;
    grid->cells[0][1] = 8;
    grid->cells[0][2] = 8;

    add_random_number_to_grid_Expect(grid);
    update_play_scene(&game_state, BUTTON_UP);
    
    TEST_ASSERT_EQUAL(16, grid->cells[0][0]);
    TEST_ASSERT_EQUAL(8, grid->cells[0][1]);
    memset(grid, 0, sizeof(*grid));

    /* Test slide down */
    grid->cells[0][0] = 8;
    grid->cells[0][1] = 8;
    grid->cells[0][2] = 8;

    add_random_number_to_grid_Expect(grid);
    update_play_scene(&game_state, BUTTON_DOWN);
    
    TEST_ASSERT_EQUAL(16, grid->cells[0][3]);
    TEST_ASSERT_EQUAL(8, grid->cells[0][2]);
    memset(grid, 0, sizeof(*grid));
}

/**
 * @brief Test that when no number can move, no number is added to the grid.
 *        The player is not allowed to stall for numbers like this.
 */
void test_no_random_number_added_when_nothing_moves()
{
    /* Set up the game */
    grid->cells[0][0] = 8;

    /* By not expecting the random number call, cmock will verify it did not happen */
    update_play_scene(&game_state, BUTTON_LEFT);

    /* Verify the number did not move */
    TEST_ASSERT_EQUAL(8, grid->cells[0][0]);
}

/**
 * @brief Verify that the game is considered lost when nothing can move
 */
void test_detects_lost_position()
{
    /* Set up the game to be lost */
    for (int x = 0; x < 4; x++)
    {
        for (int y = 0; y < 4; y++)
        {
            if ((x + y) % 2 == 0)
            {
                grid->cells[x][y] = 2;
            }
            else
            {
                grid->cells[x][y] = 4;
            }
        }
    }

    /* Try to move */
    use_lose_characters_Expect();
    update_play_scene(&game_state, BUTTON_LEFT);

    /* Check we are now in a lost position */
    TEST_ASSERT_EQUAL(SCENE_LOSE, game_state.scene);
}

/**
 * @brief Verify that the game is considered won as soon as 2048 is made.
 */
void test_detects_won_position()
{
    /* Set up game to be won */
    grid->cells[0][0] = 1024;
    grid->cells[1][0] = 1024;

    /* Win the game */
    add_random_number_to_grid_Expect(grid);
    use_win_characters_Expect();
    update_play_scene(&game_state, BUTTON_LEFT);

    /* Check we are on the win screen */
    TEST_ASSERT_EQUAL(SCENE_WIN, game_state.scene);
}

/**
 * @brief Test that the player can quit the current game return to the start scene with the back button
 */
void test_back_button_returns_to_start_scene()
{
    /* Initialise the play scene */
    init_random_Expect();
    use_play_characters_Expect();
    add_random_number_to_grid_Expect(grid);
    add_random_number_to_grid_Expect(grid);
    init_play_scene(&game_state);

    /* Pretend to hit the back button */
    update_play_scene(&game_state, BUTTON_BACK);

    /* Check we are now at the start scene */
    TEST_ASSERT_EQUAL(SCENE_START, game_state.scene);
}