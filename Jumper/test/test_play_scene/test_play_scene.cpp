#include <unity.h>
#include <Graphics.hpp>
#include <play_scene.h>
#include <unity_extensions.h>

extern position get_position_for_cell(int x, int y);

/**
 * @brief Test that the coordinate calculation for a cell is working
 * 
 */
void test_get_position_for_cell_uses_both_rectangles()
{
    TEST_ASSERT_EQUAL_POSITION(2, 0, get_position_for_cell(0, 0));
}
