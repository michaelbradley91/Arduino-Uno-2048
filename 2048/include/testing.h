#pragma once

/**
 * @brief Intercept certain definitions to support compilation and testing
 */
#ifdef PIO_UNIT_TESTING

#define MAIN_LOOP main_loop
#define MAIN_SETUP main_setup
#define STATIC 
#define SERIAL_BEGIN(SPEED) 

#else

#define MAIN_LOOP loop
#define MAIN_SETUP setup
#define STATIC static
#define SERIAL_BEGIN(SPEED) Serial.begin(SPEED)

#endif
