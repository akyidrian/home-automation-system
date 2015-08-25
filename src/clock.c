/**
 * @file clock.c
 * @version 01.06.2011
 * @authors Aydin Arik, Kevin Doran, Tim Grunshaw
 *
 * Contains the HAS clock related functions, including initialisation and a time
 * increment function.
 */


#include "clock.h"
#include "Board.h"
#include "display.h"
#include "boolean.h"


/*
 * Enable the peripheral clock, set pre-scaler at 2000 then restart.
 */
void clockInitialise(void){
    AT91F_PMC_EnablePeriphClock ( AT91C_BASE_PMC, 1 << AT91C_ID_PIOA ) ;
    volatile AT91PS_RTTC pRTTC = AT91C_BASE_RTTC;
    AT91F_RTTSetTimeBase(pRTTC, 2000);
    AT91F_RTTRestart(pRTTC);
}

/*
 * Read the RTT value, and if greater than a ONE_MINUTE reset & return TRUE.
 */
bool clockCheck(void){
    volatile AT91PS_RTTC pRTTC = AT91C_BASE_RTTC;
    pRTTC->RTTC_RTMR = 0x0008000;
   if (AT91F_RTTReadValue(pRTTC) > ONE_MINUTE )
   {
        AT91F_RTTRestart(pRTTC);
        return TRUE;
    }
    return FALSE;
}

/**
 * A pause loop that runs for MAX_PAUSE iterations.
 */
void clockPause(void){
    unsigned int waiting_time = 0;
    while(waiting_time++ < MAX_PAUSE);
}

/*
*   Increment time by 1 minute.
*/
void clockIncrement( volatile time_t* time)
{
    if(time->minutes == 59)
    {
        time->minutes = 0;
        if(time->hours == 23)
        {
            time->hours = 0;
        }
        else
        {
            time->hours++;
        }
    }
    else
    {
        time->minutes++;
    }
}
