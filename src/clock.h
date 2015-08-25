/**
 * @file clock.h
 * @version 01.06.2011
 * @authors Aydin Arik, Kevin Doran, Tim Grunshaw
 *
 * Contains the HAS clock related functions, including initialisation and a time
 * increment function.
 */

#ifndef CLOCK_H
#define CLOCK_H

#include "boolean.h"


/**
 * The count that the clockPause() function counts to before continuing. Used to
 * slow down the main loop speed so that the SAM7 clock works correctly.
 */
#define MAX_PAUSE           500


/**
 *  Defines the RTT read value that closely corresponds to 1 minute.
 */
#define ONE_MINUTE          51


/**
 *  Define the time_t datatype used to store all time information.
 */
typedef struct
{
    unsigned int hours;
    unsigned int minutes;
} time_t;


/**
 * Configures enables clock and system timer. Sets the system timer going.
 */
void clockInitialise(void);


/**
 * Checks to see if a minute has passed since this function was last called.
 * Should therefore be called regularly if used to keep track of time.
 *
 * @return TRUE when a minute has passed, FALSE otherwise.
 */
bool clockCheck(void);


/**
 *  Function that pauses for a small amount of time to solve hardware issues
 *  with the system clock.
 */
void clockPause(void);


/**
 * Increment the time passed in the argument by one minute.
 */
void clockIncrement(volatile time_t*);

#endif
