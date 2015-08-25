/*
 *  TC_PWM.h
 *
 *
 *  Created by steve weddell on 17/05/07.
 *  Copyright 2007 ECE, UC. All rights reserved.
 *  Based on Atmel's PWM Timer Application Note
 *
 */

#ifndef TC_PWM_H
#define TC_PWM_H


#define	TC_CLKS_MCLK2			0x0			// MCLK / 2; 24,027,420 Hz
#define	TC_EEVT_XC0				0x400		// Clock invert
#define	TC_CPCTRG				0x4000		// RC compare trigger enable
#define	TC_WAVE					0x8000		// Wave = Waveform generation
#define	TC_ACPA_TOGGLE_OUTPUT	0x30000		// Register A compare toggle TIOA
#define	TC_ACPC_TOGGLE_OUTPUT	0xC0000		// Register C compare toggle TIOA
#define	TC_ASWTRG_SET_OUTPUT	0x400000	// Software trigger or TIOA
#define	TC_BCPB_TOGGLE_OUTPUT	0x3000000	// Register C compare toggle TIOB
#define	TC_BCPC_TOGGLE_OUTPUT	0xC000000	// Register B compare toggle TIOB
#define	TC_BSWTRG_SET_OUTPUT	0x40000000	// software trigger set TIOB

// TC_CCR timer control register bit deinitions
#define	TC_CLKEN				0x1	 // enable timer clock
#define	TC_CLKDIS				0x2	 // no effect
#define TC_SWTRG				0x4	 // software trigger asserted

// PIO Controller definitions
//#define	PIOTIOA1				4 // Timer 1, Signal A
//#define PIOTIOB1				5 // Timer 1, Signal B

void soundInitialise(void);
void emitSound(void);
void disableSound(void);

#endif
