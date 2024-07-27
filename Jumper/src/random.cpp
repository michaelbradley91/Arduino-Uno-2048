#include <Arduino.h>
#include <Graphics.hpp>
#include <game_state.h>
#include <random.h>

#define RANDOM_ANALOG_PIN A5

/**
 * @brief Get a sort of random byte
 * 
 * @return unsigned long - the random byte found
 */
static unsigned long get_random_byte()
{
    delay(5);
    return (unsigned long)(analogRead(RANDOM_ANALOG_PIN) & 0xFF);
}

/**
 * @brief Initialise the random number generator
 */
void init_random(void)
{
    unsigned long random_value = millis();
    for (unsigned long i = 0; i < sizeof(random_value); i++)
    {
        random_value += (get_random_byte() << (i * 8));
    }

    randomSeed(random_value);
}

/**
 * @brief Add a random number to the given grid. If the grid is full, nothing
 *        is added
 * 
 * @param grid - the grid to add a number to
 */
void add_random_number_to_grid(Grid *grid)
{
    /* Count the number of free cells first */
    int number_free_cells = 0;
    for (int x = 0; x < 4; x++)
    {
        for (int y = 0; y < 4; y++)
        {
            if (grid->cells[x][y] == 0)
            {
                number_free_cells++;
            }
        }
    }
    /* Decide which cell we're adding to */
    int free_cell = (int)random(number_free_cells);

    /* Decide if we are adding a 2 or a 4 */
    int cell_value = 2;
    if (random(10) == 9)
    {
        cell_value = 4;
    }

    /* Populate the grid */
    number_free_cells = 0;
    for (int x = 0; x < 4; x++)
    {
        for (int y = 0; y < 4; y++)
        {
            if (grid->cells[x][y] == 0)
            {
                if (number_free_cells == free_cell)
                {
                    grid->cells[x][y] = cell_value;
                }
                number_free_cells++;
            }
        }
    }
}