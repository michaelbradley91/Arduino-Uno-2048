#include <unity.h>
#include <calculator.h>

int GlobalExpectCount;
int GlobalVerifyOrder;

void setUp(void) {
}

void test_calculator_works()
{
    TEST_ASSERT_EQUAL(7, add_numbers(3, 4));
}

void tearDown(void) {
    // clean stuff up here
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_calculator_works);
    UNITY_END();

    return 0;
}