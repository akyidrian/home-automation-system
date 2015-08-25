/**
 * @file tasks.c
 * @version 01.06.2011
 * @authors Aydin Arik, Kevin Doran, Tim Grunshaw
 *
 * A file that contains the timer tasks and non-timer tasks run by the kernel
 * when they are due or set active.
 */


#include "tasks.h"
#include "clock.h"
#include "led.h"
#include "Board.h"
#include "ir_sensor.h"
#include "sound.h"
#include "kernel.h"
#include "state.h"

time_t timer1Start = {0, 0};
time_t timer2Start = {0, 0};
time_t timer1End = {0, 0};
time_t timer2End = {0, 0};
time_t timerAlarmStart = {0, 0};
time_t timerAlarmEnd = {0, 0};
time_t light1Off = {0, 0};
time_t light2Off = {0, 0};


void (*timerTasks[NUM_TIMERS]) (void) =
{
        turnOnAppliance1Task,
        turnOnAppliance2Task,
        turnOffAppliance1Task,
        turnOffAppliance2Task,
        turnOnAlarmTask,
        turnOffAlarmTask,
        light1OffTask,
        light2OffTask
};

void (*nonTimerTasks[NUM_NON_TIMER_TASKS]) (time_t*) = { checkLights };

time_t* timers[NUM_TIMERS] = {&timer1Start, &timer2Start, &timer1End, &timer2End,
        &timerAlarmStart, &timerAlarmEnd, &light1Off, &light2Off};


/*
 *
 */
void turnOnAppliance1Task()
{
    turnOnLed(1);
}


/*
 *
 */
void turnOnAppliance2Task()
{
    turnOnLed(2);
}


/*
 *
 */
void turnOffAppliance1Task()
{
    turnOffLed(1);
}

/*
 *
 */
void turnOffAppliance2Task()
{
    turnOffLed(2);
}


/*
 *
 */
void turnOnAlarmTask()
{
    emitSound();
    state = ALARM_STATE;
}

/*
 *
 */
void turnOffAlarmTask()
{
    disableSound();
}


/*
 *
 */
void light1OffTask()
{
    // Turn the lights off again.
    turnOffLight1();

    // Reset the timer to 00:00
    light1Off.hours = 0;
    light1Off.minutes = 0;
}


/*
 *
 */
void light2OffTask()
{
    // Turn the lights off again.
    turnOffLight2();

    // Reset the timer to 00:00
    light2Off.hours = 0;
    light2Off.minutes = 0;
}


/*
 *
 */
void checkLights(time_t* theTime)
{
    /**
     * Light One
     */
    if(AT91F_PIO_GetInput(AT91C_BASE_PIOA) & (LIGHT_1_SENSOR) &&
            theTime->hours > NIGHT_START && theTime->hours < NIGHT_END)
    {
        // Turn on the light if the Emitter --> Sensor link is broken.
        turnOnLight1();

        /*
         * Set the light1Off timer to current time plus LIGHTS_ON_TIME minutes.
         */
        light1Off.hours = theTime->hours;
        light1Off.minutes = theTime->minutes;

        int i;
        for(i = 0; i < LIGHTS_ON_TIME; i++)
        {
            clockIncrement(&light1Off);
        }
    }

    /**
     * Light Two
     */
    if(AT91F_PIO_GetInput(AT91C_BASE_PIOA) & (LIGHT_2_SENSOR) &&
            theTime->hours > NIGHT_START && theTime->hours < NIGHT_END)
    {
        // Turn on the light if the Emitter --> Sensor link is broken.
        turnOnLight2();

        /*
         * Set the light1Off timer to current time plus LIGHTS_ON_TIME minutes.
         */
        light1Off.hours = theTime->hours;
        light1Off.minutes = theTime->minutes;

        int i;
        for(i = 0; i < LIGHTS_ON_TIME; i++)
        {
            clockIncrement(&light1Off);
        }
    }
}
