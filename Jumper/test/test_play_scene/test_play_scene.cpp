#include <unity.h>
#include <Graphics.hpp>
#include <play_scene.h>
#include <unity_extensions.h>

int GlobalExpectCount;
int GlobalVerifyOrder;

extern position get_position_for_cell(int x, int y);

void setUp(void) {
}

/**
 * @brief Test that the coordinate calculation for a cell is working
 * 
 */
void test_get_position_for_cell_uses_both_rectangles()
{
    TEST_ASSERT_EQUAL_POSITION(2, 0, get_position_for_cell(0, 0));
}

void tearDown(void) {
    // clean stuff up here
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_get_position_for_cell_uses_both_rectangles);
    UNITY_END();

    return 0;
}