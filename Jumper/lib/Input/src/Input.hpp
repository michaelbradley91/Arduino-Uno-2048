#pragma once

/**
 * @brief Raw button codes received by our infrared receiver
 */
typedef enum
{
  IR_BUTTON_ONE = 12,
  IR_BUTTON_TWO = 24,
  IR_BUTTON_THREE = 94,
  IR_BUTTON_FOUR = 8,
  IR_BUTTON_FIVE = 28,
  IR_BUTTON_SIX = 90,
  IR_BUTTON_SEVEN = 66,
  IR_BUTTON_EIGHT = 82,
  IR_BUTTON_NINE = 74,
  IR_BUTTON_ZERO = 22,
  IR_BUTTON_EQ = 25,
  IR_BUTTON_ST_REPT = 13,
  IR_BUTTON_DOWN = 7,
  IR_BUTTON_UP = 9,
  IR_BUTTON_VOL_DOWN = 70,
  IR_BUTTON_VOL_UP = 21,
  IR_BUTTON_PREV = 68,
  IR_BUTTON_NEXT = 67,
  IR_BUTTON_POWER = 69,
  IR_BUTTON_FUNC_STOP = 71,
  IR_BUTTON_PLAY_PAUSE = 64,
  IR_BUTTON_UNKNOWN = -1
} IR_BUTTON;

/**
 * @brief The raw buttons received from the Wokwi remote controller
 */
typedef enum
{
    WOKWI_BUTTON_POWER = 0xA2,
    WOKWI_BUTTON_TEST = 0x22,
    WOKWI_BUTTON_MENU = 0xE2,
    WOKWI_BUTTON_MINUS = 0x98,
    WOKWI_BUTTON_PLUS = 0x2,
    WOKWI_BUTTON_RETURN = 0xC2,
    WOKWI_BUTTON_PREV = 0xE0,
    WOKWI_BUTTON_NEXT = 0x90,
    WOKWI_BUTTON_PLAY = 0xA8,
    WOKWI_BUTTON_ZERO = 0x68,
    WOKWI_BUTTON_C = 0xB0,
    WOKWI_BUTTON_ONE = 0x30,
    WOKWI_BUTTON_TWO = 0x18,
    WOKWI_BUTTON_THREE = 0x7A,
    WOKWI_BUTTON_FOUR = 0x10,
    WOKWI_BUTTON_FIVE = 0x38,
    WOKWI_BUTTON_SIX = 0x5A,
    WOKWI_BUTTON_SEVEN = 0x42,
    WOKWI_BUTTON_EIGHT = 0x4A,
    WOKWI_BUTTON_NINE = 0x52,
    WOKWI_BUTTON_UNKNOWN = -1
} WOKWI_BUTTON;

/**
 * @brief A logical game button.
 * 
 * This is intended as actual input to the game, as it will
 * translate between different controllers automatically.
 */

void init_input(int wokwi_pin, int ir_receive_pin);
const char *raw_button_to_str(int button);
int is_button_pressed(void);
int get_raw_button_pressed(void);
