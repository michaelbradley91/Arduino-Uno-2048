#include <unity.h>
#include <GraphicsFake.hpp>
#include <GraphicsStub.hpp>
#include <randomFake.h>
#include <unity_extensions.h>
#include <string.h>
#include <start_scene.h>

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
 * @brief Test that the player can go to the play scene with almost any button
 */
void test_can_go_to_play_scene_with_almost_any_button()
{
    button buttons[] = { BUTTON_DOWN, BUTTON_ENTER, BUTTON_LEFT, BUTTON_BACK, BUTTON_RIGHT, BUTTON_UP};
    for (int i = 0; i < sizeof(buttons) / sizeof(button); i++)
    {
        /* Initialise the start scene */
        init_start_scene(&game_state);

        /* Pretend to hit the correct button */
        init_random_Expect();
        use_play_characters_Expect();
        add_random_number_to_grid_Expect(grid);
        add_random_number_to_grid_Expect(grid);
        update_start_scene(&game_state, buttons[i]);

        /* Check we are now on the start screen */
        TEST_ASSERT_EQUAL(SCENE_PLAY, game_state.scene);
    }
}
