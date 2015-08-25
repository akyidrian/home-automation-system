/**
 * @file kernel.h
 * @version 01.06.2011
 * @authors Aydin Arik, Kevin Doran, Tim Grunshaw
 *
 * Contains the kernel that runs the Home Automation System. Including task
 * scheduler, time keeping, state control and four general purpose functions
 * needed by the kernel to operate correctly.
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "clock.h"
#include "boolean.h"


/**
 *  Starts the kernel, which first initialises micro-controller then enters an
 *  infinite loop of running. Call this function from a main to run the HAS.
 */
void run(void);


/**
 *  Check what state the kernel should enter next, and sets the state variable so
 *  that this is done the next loop. This is ran internally every loop.
 */
void checkState(void);


/**
 *  Used to enable time adjusting from the keypad. Used by multiple states, and
 *  in multiple tasks so is best suited to be located in the kernel file.
 *
 *  @param time_t The time to adjust.
 *  @param Digit The digit of the time to adjust (from 0 - 3).
 */
bool adjustTime(time_t* , int* );


/**
 * Simply flashes the display at about 3Hz with the time entered. Usually used
 * when adjusting a timer or the system time.
 *
 * @param Time The time to flash on the display. Usually used when adjusting a
 * timer or the system time.
 */
void flashClockDisplay(time_t* const);


/**
 * Shows the passed message for about 1 second before entering each new mode.
 * While the message is being displayed the kernel is still responsive and can
 * increment time, check states and keyPresses.
 *
 * This is used in combination with the main state switch statement to briefly
 * tell the user what state they have entered. The reason for the return value is
 * so that the kernel can continue while it is waiting, and a static counter is
 * incremented. Only when it has finished waiting does the actual case statement
 * run to the end without breaking. During this run the counter is reset, the last
 * state updated and the actual state is entered.
 *
 * @return Bool TRUE while it is still waiting, FALSE when it has finished waiting.
 */
bool waitWithMessage(char*);

int state;


#endif /* MAIN_H_ */
