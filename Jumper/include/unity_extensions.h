#pragma once

/**
 * @brief Compare two positions for equality
 */
#define TEST_ASSERT_EQUAL_POSITION(X, Y, actual) do { \
    position pos = actual; \
    TEST_ASSERT_EQUAL_INT(X, pos.x); \
    TEST_ASSERT_EQUAL_INT(Y, pos.y); \
} while(0);