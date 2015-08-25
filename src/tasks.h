/**
 * @file tasks.h
 * @version 01.06.2011
 * @authors Aydin Arik, Kevin Doran, Tim Grunshaw
 *
 * A file that contains the timer tasks and non-timer tasks run by the kernel
 * when they are due or set active.
 */

#ifndef TASKS_H_
#define TASKS_H_

#include "clock.h"
#include "timers.h"
#include "boolean.h"

enum nonTimerTasksActive {CHECK_LIGHTS = 0};

/**
 * The number of non-timer tasks.
 */
#define NUM_NON_TIMER_TASKS 1


#define LIGHTS_ON_TIME 2 // Minutes
#define NIGHT_START 18 // Hours
#define NIGHT_END 6 // Hours


/**
 * An array of function pointers to the timer tasks.
 */
void (*timerTasks[NUM_TIMERS]) (void);


/**
 * An array of function pointers to the non-timer tasks.
 */
void (*nonTimerTasks[NUM_NON_TIMER_TASKS]) (time_t*);


/**
 * An array of timers.
 */
time_t* timers[NUM_TIMERS];


time_t timer1Start;
time_t timer2Start;
time_t timer1End;
time_t timer2End;
time_t timerAlarm;
time_t timerAlarmEnd;
time_t light1Off;
time_t light2Off;


/**
 * Array of booleans indicating which non-timer tasks are active.
 */
bool nonTimerTaskActive[NUM_NON_TIMER_TASKS];


/**
 * Turns on appliance 1. (Turns on an LED)
 */
void turnOnAppliance1Task(void);


/**
 * Turns on appliance 2. (Turns on an LED)
 */
void turnOnAppliance2Task(void);


/**
 * Turns off appliance 1. (Turns off an LED)
 */
void turnOffAppliance1Task(void);


/**
 * Turns off appliance 2. (Turns off an LED)
 */
void turnOffAppliance2Task(void);


/**
 * Turns on the alarm.
 */
void turnOnAlarmTask(void);


/**
 * Checks to see if either of the lights in the automatic lighting should turn on.
 * It checks to see if the current time is between 18:00 and 06:00, and if the
 * IR sensor has been broken. If these conditions are met, it turns on the light
 * (and LED) and sets the turnLights 1 or 2 timer to turn the light off again in
 * 2 minutes.
 *
 * @param time The current system time.
 */
void checkLights(time_t*);


/**
 * Turns off the alarm.
 */
void turnOffAlarmTask(void);


/**
 * Turns off light 1. (An LED)
 */
void light1OffTask(void);


/**
 * Turns off light 2. (An LED)
 */
void light2OffTask(void);


#endif /* TASKS_H_ */
