/**
 * @file sound.c
 * @version 01.06.2011
 * @authors Aydin Arik, Kevin Doran, Tim Grunshaw
 *
 * Contains functions relevant to the Piezzo buzzer in the Home Automation System.
 */

#include "board.h"
#include "TC_PWM.h"
#include "sound.h"


/*
*
* PROBLEM: DIG1 on displays stops working because of "TCLK1" by the looks of it; can we change this?
*
* EDIT by Tim - FIXED. Set only the TIOA1 & TIOB1 ports.
*
*/


/*
 *
 */
void soundInitialise(void)
{
    volatile AT91PS_TC	pTc = AT91C_BASE_TC1;	// get a ptr to channel 1 register structure

    // First, enable the clock for the timer. Note, this is NOT the same as AT91C_ID_PIOA used before.
       AT91F_PMC_EnablePeriphClock ( AT91C_BASE_PMC, 1 << AT91C_ID_TC1); // AT91C_ID_PIOA ) ;

    // then, we configure the PIO Lines for LED outputs
       //AT91F_PIO_CfgOutput( AT91C_BASE_PIOA, 1<<11 ) ;

    // Flash an LED in debug mode
       //AT91F_PIO_SetOutput( AT91C_BASE_PIOA, 1<<11 ) ;
       //AT91F_PIO_ClearOutput( AT91C_BASE_PIOA, 1<<11) ;


       //AT91F_TC1_CfgPIO ();		// Periph. B config as, PA15 = TIOA1; PA16 = TIOB1; PA28 = TCLK1

    volatile struct _AT91S_PIO* pwm_gen;
    pwm_gen->PIO_PDR = (1<<PIOTIOA1) | (1<<PIOTIOB1);

    pTc->TC_CCR = TC_CLKDIS;	// disable the clock, just for now

	pTc->TC_CMR =								// set mode configuration
					TC_BSWTRG_SET_OUTPUT	|
					TC_BCPC_TOGGLE_OUTPUT	|
					TC_BCPB_TOGGLE_OUTPUT	|
					TC_ASWTRG_SET_OUTPUT	|
					TC_ACPC_TOGGLE_OUTPUT	|
					TC_ACPA_TOGGLE_OUTPUT	|
					TC_WAVE					|
					TC_CPCTRG				|
					TC_EEVT_XC0				|
					TC_CLKS_MCLK2 ;

    pTc->TC_RC = 0x80E8;
	pTc->TC_RB = 0x4074; // Higher pitch
	pTc->TC_RA = 0x26AC; // Lower pitch
}


/*
 *
 */
void emitSound(void)
{

    volatile AT91PS_TC	pTc = AT91C_BASE_TC1;	// get a ptr to channel 1 register structure

    pTc->TC_CCR = TC_CLKEN;	// enable the clock to produce PWM
	pTc->TC_CCR = TC_SWTRG;
}


/*
 *
 */
void disableSound(void)
{
    volatile AT91PS_TC	pTc = AT91C_BASE_TC1;	// get a ptr to channel 1 register structure
	pTc->TC_CCR = TC_CLKDIS;	// disable the clock, just for now
}
