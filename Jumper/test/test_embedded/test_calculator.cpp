
#include <unity.h>
#include <calculator.h>
#include <Arduino.h>

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_calculator_works()
{
    TEST_ASSERT_EQUAL(7, add_numbers(3, 4));
}

void setup() {
    // NOTE!!! Wait for >2 secs
    // if board doesn't support software reset via Serial.DTR/RTS
    Serial.begin(9600);
    delay(1000);

    UNITY_BEGIN();
    RUN_TEST(test_calculator_works);
    UNITY_END();
}

void loop() {

}