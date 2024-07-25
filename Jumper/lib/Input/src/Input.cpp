/**
 * @brief This module manages the interpretation of user input
 */

/* Both Wokwi and our controller use NEC encoding */
#define DECODE_NEC
#include "Input.hpp"
#include <Arduino.h>
#include <IRremote.hpp>

#define IR_RECEIVE_PIN 7

const char *IR_BUTTON_NAMES[] = {
  "One",
  "Two",
  "Three",
  "Four",
  "Five",
  "Six",
  "Seven",
  "Eight",
  "Nine",
  "Zero",
  "Eq",
  "St/Rept",
  "Down",
  "Up",
  "Volume Up",
  "Volume Down",
  "Previous",
  "Next",
  "Power",
  "Func/Stop",
  "Play/Pause",
  "Unknown"
};

const char *WOKWI_BUTTON_NAMES[] = {
  "Power",
  "Test",
  "Menu",
  "Minus",
  "Plus",
  "Return",
  "Prev",
  "Next",
  "Play",
  "Zero",
  "C",
  "One",
  "Two",
  "Three",
  "Four",
  "Five",
  "Six",
  "Seven",
  "Eight",
  "Nine",
  "Unknown"
};

unsigned char is_wokwi = 0;

/**
 * @brief Initialise the input library
 * 
 * @param wokwi_pin - a pin to test if we are in the Wokwi simulator
 * @param ir_receive_pin - the pin receiving IR input
 */
void init_input(int wokwi_pin, int ir_receive_pin)
{
  pinMode(wokwi_pin, INPUT);
  /* Are we running inside the Wokwi simulator? */
  if (digitalRead(wokwi_pin) == HIGH)
  {
    is_wokwi = 1;
  }
  IrReceiver.begin(ir_receive_pin, ENABLE_LED_FEEDBACK);
}

static const char *ir_button_to_str(IR_BUTTON button)
{
  switch (button)
  {
    case IR_BUTTON_ONE:
      return IR_BUTTON_NAMES[0];
    case IR_BUTTON_TWO:
      return IR_BUTTON_NAMES[1];
    case IR_BUTTON_THREE:
      return IR_BUTTON_NAMES[2];
    case IR_BUTTON_FOUR:
      return IR_BUTTON_NAMES[3];
    case IR_BUTTON_FIVE:
      return IR_BUTTON_NAMES[4];
    case IR_BUTTON_SIX:
      return IR_BUTTON_NAMES[5];
    case IR_BUTTON_SEVEN:
      return IR_BUTTON_NAMES[6];
    case IR_BUTTON_EIGHT:
      return IR_BUTTON_NAMES[7];
    case IR_BUTTON_NINE:
      return IR_BUTTON_NAMES[8];
    case IR_BUTTON_ZERO:
      return IR_BUTTON_NAMES[9];
    case IR_BUTTON_EQ:
      return IR_BUTTON_NAMES[10];
    case IR_BUTTON_ST_REPT:
      return IR_BUTTON_NAMES[11];
    case IR_BUTTON_DOWN:
      return IR_BUTTON_NAMES[12];
    case IR_BUTTON_UP:
      return IR_BUTTON_NAMES[13];
    case IR_BUTTON_VOL_DOWN:
      return IR_BUTTON_NAMES[14];
    case IR_BUTTON_VOL_UP:
      return IR_BUTTON_NAMES[15];
    case IR_BUTTON_PREV:
      return IR_BUTTON_NAMES[16];
    case IR_BUTTON_NEXT:
      return IR_BUTTON_NAMES[17];
    case IR_BUTTON_POWER:
      return IR_BUTTON_NAMES[18];
    case IR_BUTTON_FUNC_STOP:
      return IR_BUTTON_NAMES[19];
    case IR_BUTTON_PLAY_PAUSE:
      return IR_BUTTON_NAMES[20];
    default:
      return IR_BUTTON_NAMES[21];
  }
}

static const char *wokwi_button_to_str(WOKWI_BUTTON button)
{
  switch (button)
  {
    case WOKWI_BUTTON_POWER:
      return WOKWI_BUTTON_NAMES[0];
    case WOKWI_BUTTON_TEST:
      return WOKWI_BUTTON_NAMES[1];
    case WOKWI_BUTTON_MENU:
      return WOKWI_BUTTON_NAMES[2];
    case WOKWI_BUTTON_MINUS:
      return WOKWI_BUTTON_NAMES[3];
    case WOKWI_BUTTON_PLUS:
      return WOKWI_BUTTON_NAMES[4];
    case WOKWI_BUTTON_RETURN:
      return WOKWI_BUTTON_NAMES[5];
    case WOKWI_BUTTON_PREV:
      return WOKWI_BUTTON_NAMES[6];
    case WOKWI_BUTTON_NEXT:
      return WOKWI_BUTTON_NAMES[7];
    case WOKWI_BUTTON_PLAY:
      return WOKWI_BUTTON_NAMES[8];
    case WOKWI_BUTTON_ZERO:
      return WOKWI_BUTTON_NAMES[9];
    case WOKWI_BUTTON_C:
      return WOKWI_BUTTON_NAMES[10];
    case WOKWI_BUTTON_ONE:
      return WOKWI_BUTTON_NAMES[11];
    case WOKWI_BUTTON_TWO:
      return WOKWI_BUTTON_NAMES[12];
    case WOKWI_BUTTON_THREE:
      return WOKWI_BUTTON_NAMES[13];
    case WOKWI_BUTTON_FOUR:
      return WOKWI_BUTTON_NAMES[14];
    case WOKWI_BUTTON_FIVE:
      return WOKWI_BUTTON_NAMES[15];
    case WOKWI_BUTTON_SIX:
      return WOKWI_BUTTON_NAMES[16];
    case WOKWI_BUTTON_SEVEN:
      return WOKWI_BUTTON_NAMES[17];
    case WOKWI_BUTTON_EIGHT:
      return WOKWI_BUTTON_NAMES[18];
    case WOKWI_BUTTON_NINE:
      return WOKWI_BUTTON_NAMES[19];
    default:
      return WOKWI_BUTTON_NAMES[20];
  }
}

/**
 * @brief Get a string representation of a button pressed
 * 
 * @param button - the raw button code
 * @return char* - a string representation of the button. Does not need to be freed
 */
const char *raw_button_to_str(int button)
{
  if (is_wokwi)
  {
    return wokwi_button_to_str((WOKWI_BUTTON)button);
  }
  return ir_button_to_str((IR_BUTTON)button);
}

/**
 * @brief Check if a button has been pressed without consuming the input
 * 
 * @return int - 0 if nothing is available, and 1 otherwise
 */
int is_button_pressed(void)
{
  if (IrReceiver.available())
  {
    return 1;
  }
  return 0;
}

/**
 * @brief Get the raw button pressed code.
 * 
 * @return int - the raw infrared code, or -1 if no button is pressed
 */
int get_raw_button_pressed(void)
{
  if (is_button_pressed())
  {
    if (IrReceiver.decode()) {
      IrReceiver.printIRResultShort(&Serial);
      uint16_t command = IrReceiver.decodedIRData.command;
      delay(100);  // wait a bit
      IrReceiver.resume();
      return (int)command;
    }
  }
  return -1;
}

int get_button_pressed()
{
  return 0;
}