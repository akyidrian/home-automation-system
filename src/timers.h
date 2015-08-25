/**
 * @file timers.h
 * @version 01.06.2011
 * @authors Aydin Arik, Kevin Doran, Tim Grunshaw
 *
 * Contains functions relevant to checking timers.
 */

#ifndef TIMERS_H_
#define TIMERS_H_

#include "boolean.h"
#include "clock.h"

/**
 * The number of timers being used in the HAS.
 */
#define NUM_TIMERS 8

/**
 * Check to see if the system time matches any of the timers, and returns a
 * pointer to an array of bools indicating which timers (if any) were matched.
 *
 * @param time* A pointer to the current system time.
 * @param time*[] A pointer an array of timers to check.
 * @return bool* A pointer to an array of booleans indication TRUE for any timers
 * matched.
 */
bool* checkTimers(time_t* , time_t*[]);


/**
 * Used by checkTimers to check if a timer was matched.
 *
 * @param time* One of two times to compare.
 * @param time* One of two times to compare.
 * @return bool TRUE if they match, FALSE otherwise.
 */
bool isTimerMatched(time_t* , time_t*);

#endif /* TIMERS_H_ */
