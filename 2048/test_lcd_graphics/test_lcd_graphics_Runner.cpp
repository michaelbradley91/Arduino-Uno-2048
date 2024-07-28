/* AUTOGENERATED FILE. DO NOT EDIT. */

/*=======Automagically Detected Files To Include=====*/
#include "unity.h"
#include "stdio.h"
#include <Graphics.hpp>
#include <Arduino.h>
#include <pins.h>
#include "CException.h"

int GlobalExpectCount;
int GlobalVerifyOrder;
char* GlobalOrderError;

/*=======External Functions This Runner Calls=====*/
extern void setUp(void);
extern void tearDown(void);
extern void test_reset_screen_does_clear_the_screen();
extern void test_draw_number_given_valid_number_draws_the_correct_number();
extern void test_draw_number_with_invalid_number_clears_cell();
extern void test_draw_text_with_valid_text_works();
extern void test_draw_text_with_text_too_long_truncates_text();
extern void test_draw_bytes_with_valid_bytes_handles_null_correctly();
extern void test_draw_bytes_with_bytes_too_long_truncates_bytes();


/*=======Mock Management=====*/
static void CMock_Init(void)
{
  GlobalExpectCount = 0;
  GlobalVerifyOrder = 0;
  GlobalOrderError = NULL;
}
static void CMock_Verify(void)
{
}
static void CMock_Destroy(void)
{
}

/*=======Suite Setup=====*/
void suiteSetUp(void)
{
Serial.begin(115200); init_graphics(LCD_PINS); delay(1000);
}

/*=======Suite Teardown=====*/
int suiteTearDown(int num_failures)
{
return num_failures; } void loop() {
}

/*=======Test Reset Options=====*/
void resetTest(void);
void resetTest(void)
{
  tearDown();
  CMock_Verify();
  CMock_Destroy();
  CMock_Init();
  setUp();
}
void verifyTest(void);
void verifyTest(void)
{
  CMock_Verify();
}

/*=======Test Runner Used To Run Each Test=====*/
static void run_test(UnityTestFunction func, const char* name, UNITY_LINE_TYPE line_num)
{
    Unity.CurrentTestName = name;
    Unity.CurrentTestLineNumber = (UNITY_UINT) line_num;
#ifdef UNITY_USE_COMMAND_LINE_ARGS
    if (!UnityTestMatches())
        return;
#endif
    Unity.NumberOfTests++;
    UNITY_CLR_DETAILS();
    UNITY_EXEC_TIME_START();
    CMock_Init();
    if (TEST_PROTECT())
    {
        volatile CEXCEPTION_T e;
        Try {
            setUp();
            func();
        } Catch(e) {
            TEST_ASSERT_EQUAL_HEX32_MESSAGE(CEXCEPTION_NONE, e, "Unhandled Exception!");
        }
    }
    if (TEST_PROTECT())
    {
        tearDown();
        CMock_Verify();
    }
    CMock_Destroy();
    UNITY_EXEC_TIME_STOP();
    UnityConcludeTest();
}

/*=======Parameterized Test Wrappers=====*/

/*=======MAIN=====*/
int run(void); void setup() {run();} int run(void);
int run(void)
{
  suiteSetUp();
  UnityBegin("test/remote/test_lcd_graphics/test_lcd_graphics.cpp");
  run_test(test_reset_screen_does_clear_the_screen, "test_reset_screen_does_clear_the_screen", 53);
  run_test(test_draw_number_given_valid_number_draws_the_correct_number, "test_draw_number_given_valid_number_draws_the_correct_number", 80);
  run_test(test_draw_number_with_invalid_number_clears_cell, "test_draw_number_with_invalid_number_clears_cell", 113);
  run_test(test_draw_text_with_valid_text_works, "test_draw_text_with_valid_text_works", 135);
  run_test(test_draw_text_with_text_too_long_truncates_text, "test_draw_text_with_text_too_long_truncates_text", 153);
  run_test(test_draw_bytes_with_valid_bytes_handles_null_correctly, "test_draw_bytes_with_valid_bytes_handles_null_correctly", 168);
  run_test(test_draw_bytes_with_bytes_too_long_truncates_bytes, "test_draw_bytes_with_bytes_too_long_truncates_bytes", 191);

  return suiteTearDown(UNITY_END());
}