/**
 * @file display.h
 * @version 01.06.2011
 * @authors Aydin Arik, Kevin Doran, Tim Grunshaw
 *
 * Contains functions needed to use the 7 segment display to show characters.
 */

#ifndef DISPLAY_H
#define DISPLAY_H

#include "boolean.h"
#include "clock.h"

/**
 * Define the digit of 7 segment display.
 */
#define DIG0 1<<28
#define DIG1 1<<29
#define DIG2 1<<30
#define DIG3 1<<31
#define DIG_MASK (DIG0 | DIG1 | DIG2 | DIG3)

/**
 * Define the LED segments on the 7 segment display.
 */
#define LED_A 1<<22
#define LED_B 1<<20
#define LED_C 1<<24
#define LED_D 1<<26
#define LED_E 1<<27
#define LED_F 1<<21
#define LED_G 1<<23
#define DOT 1<<25


/**
 * Define commonly used number and letter representations.
 */
#define ZERO (LED_A | LED_B | LED_C | LED_D | LED_E | LED_F)
#define ONE (LED_B | LED_C)
#define TWO (LED_A | LED_B | LED_G | LED_E | LED_D)
#define THREE (LED_A | LED_B | LED_G | LED_C | LED_D)
#define FOUR (LED_F | LED_G | LED_B | LED_C)
#define FIVE (LED_A | LED_F | LED_G | LED_C | LED_D )
#define SIX (LED_A | LED_F | LED_G | LED_C | LED_D | LED_E)
#define SEVEN (LED_A | LED_B | LED_C)
#define EIGHT (LED_A | LED_B | LED_C | LED_D | LED_E | LED_F | LED_G)
#define NINE (LED_A | LED_B | LED_C | LED_F | LED_G)
#define LETTER_A (LED_A | LED_B | LED_C | LED_E | LED_F | LED_G)
#define LETTER_C (LED_A | LED_D | LED_E | LED_F)
#define LETTER_E (LED_A | LED_D | LED_E | LED_F | LED_G)
#define LETTER_F (LED_A | LED_E | LED_F | LED_G)
#define LETTER_H (LED_B | LED_C | LED_E | LED_F | LED_G)
#define LETTER_I (LED_E | LED_F)
#define LETTER_J (LED_B | LED_C | LED_D)
#define LETTER_L (LED_D | LED_E | LED_F)
#define LETTER_S (LED_A | LED_F | LED_G | LED_C | LED_D )
#define LETTER_n (LED_C | LED_E | LED_G)
#define LETTER_o (LED_C | LED_D | LED_E | LED_G)
#define LETTER_O ZERO
#define LETTER_P (LED_A | LED_B | LED_E | LED_F | LED_G)
#define LETTER_t (LED_D | LED_E | LED_F | LED_G)
#define LETTER_U (LED_B | LED_C | LED_D | LED_E | LED_F)
#define BLANK 0
#define FULL_ON (EIGHT | DOT)


/**
 * Displays a character specified by its ASCII value OR integer value for the
 * numbers 0-9.
 * @param number/letter The number or letter to display.
 * @param digit The digit to display the character on (from 0 - 3).
 * @param decimal Whether or not to have the decimal point show.
 */
void displayNum(int, int, bool);


/**
 * Display the 4 long character string specified. Is multiplexed, so must be
 * called regularly to display correctly. (>30Hz). If the letter cannot be
 * displayed then it will show as blank.
 *
 * @param String A 4 long character string.
 */
void displayString(char*);


/**
 * Display the 4 long integer string specified. Is multiplexed, so must be
 * called regularly to display correctly. (>30Hz).
 *
 * @param int A 4 long integer string.
 */
void displayIntString(int[]);


/**
 * Initialise the ports so that the display can be correctly used.
 */
void displayInitialise(void);


/**
 * displayTime takes a time_t and displays the next digit of the time every time
 * it is called. As such it should be called often (>30Hz).
 *
 * @param time The time to display.
 */
void displayTime(time_t*);

#endif
