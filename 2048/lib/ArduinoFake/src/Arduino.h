#pragma once

/**
 * @brief This file contains definitions to satisfy
 *        our use of Arduino.h when running native tests
 */

#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>

/**
 * @brief Fake types
 */
#define byte uint8_t

/**
 * @brief Fake macros
 */
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

/**
 * @brief Fake pins
 */
#define A5 5

/**
 * @brief Function substitutes
 */
void delay(unsigned long ms);


/**
 * @brief Make our own printer available
 */
class Printer
{
    public:
        static void begin(int rate)
        {

        }
        static void println(const char *text)
        {
            printf("%s\n", text);
        }
        static void print(const char *text)
        {
            printf("%s", text);
        }
        static void println(int x)
        {
            printf("%d\n", x);
        }
        static void print(int x)
        {
            printf("%d", x);
        }
};

extern class Printer Serial;
