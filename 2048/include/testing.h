#pragma once

/**
 * @brief Intercept certain definitions to support compilation and testing
 */
#ifdef PIO_UNIT_TESTING

#define LOOP main_loop
#define SETUP main_setup
#define STATIC 

#else

#define LOOP loop
#define SETUP setup
#define STATIC static

#endif
