/**
 * @file sound.h
 * @version 01.06.2011
 * @authors Aydin Arik, Kevin Doran, Tim Grunshaw
 *
 * Contains functions relevant to the Piezo buzzer in the Home Automation System.
 */

#ifndef SOUND_H_
#define SOUND_H_


#include "board.h"
#include "TC_PWM.h"

#define PIOTIOA1 4 // Timer 1 Signal A: Refer to page8 PWM App note.
#define PIOTIOB1 5 // As above but Signal B


/**
 * Initialise the PWM and ports needed to operate the piezo buzzer.
 */
void soundInitialise(void);


/**
 * Emit sound at 1kHz through the piezo buzzer.
 */
void emitSound(void);


/**
 * Turn off the piezo buzzer. If already off this function does nothing.
 */
void disableSound(void);


#endif /* SOUND_H_ */
