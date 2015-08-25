/**
 * @file led.c
 * @version 01.06.2011
 * @authors Aydin Arik, Kevin Doran, Tim Grunshaw
 *
 * Contains functions relevant to the LEDs used in the Home Automation System.
 */


#include "led.h"


/*
 *
 */
void ledInitialise()
{
    // Initialise the Appliance LED's
    AT91F_PIO_CfgOutput(  AT91C_BASE_PIOA, (LED_0 | LED_1));
    AT91F_PIO_SetOutput(  AT91C_BASE_PIOA, (LED_0 | LED_1));

    // Initialise the IR sensed automatic lights
    AT91F_PIO_CfgOutput(  AT91C_BASE_PIOA, (LED_2 | LED_3));
    AT91F_PIO_SetOutput(  AT91C_BASE_PIOA, (LED_2 | LED_3));
}


/*
 *
 */
void turnOnLed(int led)
{
    int ledBit = 0;

    switch (led)
    {
    case 1:
        ledBit = LED1;
        break;
    case 2:
        ledBit = LED2;
        break;
    case 3:
        ledBit = LED3;
        break;
    case 4:
        ledBit = LED4;
        break;
    }

    AT91F_PIO_ClearOutput( AT91C_BASE_PIOA, ledBit);
}


/*
 *
 */
void turnOffLed(int led)
{
    int ledBit = 0;

    switch (led)
    {
    case 1:
        ledBit = LED1;
        break;
    case 2:
        ledBit = LED2;
        break;
    case 3:
        ledBit = LED3;
        break;
    case 4:
        ledBit = LED4;
        break;
    }

    AT91F_PIO_SetOutput( AT91C_BASE_PIOA, ledBit);

}

