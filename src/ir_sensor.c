/**
 * @file ir_sensor.c
 * @version 01.06.2011
 * @authors Aydin Arik, Kevin Doran, Tim Grunshaw
 *
 * Contains functions related to the IR Sensor and automated lighting system in
 * the Home Automation System.
 */

#include "ir_sensor.h"
#include "led.h"


void turnOnLight1(void)
{
    turnOnLed(3);
}
void turnOnLight2(void)
{
    turnOnLed(4);
}

void turnOffLight1(void)
{
    turnOffLed(3);
}
void turnOffLight2(void)
{
    turnOffLed(4);
}

