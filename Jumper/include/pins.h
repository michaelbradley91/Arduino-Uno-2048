#pragma once

/**
 * @brief Constant values for our PINS
 */

/**
 * @brief Where the infrared receiver is getting its input
 */
#define IR_RECEIVE_PIN 7

/**
 * @brief Pin to identify if we are in the Wokwi simulator
 */
#define WOKWI_PIN 13

/**
 * @brief How the LCD display is connected
 */
#define LCD_PINS {register_select: 12, enable: 11, d4: 5, d5: 4, d6: 3, d7: 2}
