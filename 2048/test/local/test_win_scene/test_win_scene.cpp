#include <unity.h>
#include <GraphicsFake.hpp>
#include <GraphicsStub.hpp>
#include <randomFake.h>
#include <unity_extensions.h>
#include <string.h>
#include <win_scene.h>

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
 * @brief Test that the player can return to the start scene with the back button
 */
void test_back_button_moves_to_start_scene()
{
    /* Initialise the win scene */
    use_win_characters_Expect();
    init_win_scene(&game_state);

    /* Pretend to hit the back button */
    update_win_scene(&game_state, BUTTON_BACK);

    /* Check we are now on the play screen */
    TEST_ASSERT_EQUAL(SCENE_START, game_state.scene);
}
