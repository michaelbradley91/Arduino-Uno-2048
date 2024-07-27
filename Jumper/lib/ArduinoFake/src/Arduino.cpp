#include <stdio.h>
#include "Arduino.h"

/**
 * @brief Delay is disabled in native builds since it
 *        is probably not required
 * 
 * @param ms - the milliseconds to delay for, which are ignored
 */
void delay(unsigned long ms)
{
    return;
}

Printer Serial;
