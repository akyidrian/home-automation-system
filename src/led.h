/**
 * @file led.h
 * @version 01.06.2011
 * @authors Aydin Arik, Kevin Doran, Tim Grunshaw
 *
 * Contains functions relevant to the LEDs used in the Home Automation System.
 */

#ifndef LED_H_
#define LED_H_

/**
 * Define what ports the LEDs are connected to.
 */
#define LED_0 (1 << 11)
#define LED_1 (1 << 12)
#define LED_2 (1 << 18)
#define LED_3 (1 << 19)


#include "Board.h"

/**
 * ledInitialise initialises the ports needed to control the two appliance LED's
 * and the two automatic lights.
 */
void ledInitialise(void);

/**
 * Turn on the led specified by the argument. (1 - 4).
 *
 * @param LED The Led to turn on.
 */
void turnOnLed(int);


/**
 * Turn off the led specified by the argument. (1 - 4).
 *
 * @param LED the Led to turn off.
 */
void turnOffLed(int);


#endif /* LED_H_ */
