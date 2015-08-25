/**
 * @file timers.h
 * @version 01.06.2011
 * @authors Aydin Arik, Kevin Doran, Tim Grunshaw
 *
 * Contains functions relevant to checking timers.
 */

#include "timers.h"


bool timerMatch[NUM_TIMERS];


// Cycle through all timers with current time to check if they have matched.
// Return an array of matched timers.
bool* checkTimers(time_t* currTime, time_t* timers[])
{
    int i;

    for(i = 0; i < NUM_TIMERS; i++)
    {
        // Makes sure all timersMathes are FALSE to begin with.
        timerMatch[i] = isTimerMatched(timers[i], currTime);
    }

    return timerMatch;
}


/*
 *
 */
bool isTimerMatched(time_t* timerTime, time_t* currTime)
{
    if ( (timerTime->hours == currTime->hours) && (timerTime->minutes == currTime->minutes))
    {
        return TRUE;
    }
    return FALSE;
}
