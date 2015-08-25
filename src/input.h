/**
 * @file input.h
 * @version 01.06.2011
 * @authors Aydin Arik, Kevin Doran, Tim Grunshaw
 *
 * Contains functions needed to use the keypad correctly.
 */

#ifndef INPUT_H
#define INPUT_H

#include "clock.h"
#include "boolean.h"

/**
 * Define the keypad columns and rows.
 */
#define KP_COL1 1<<3
#define KP_COL2 1<<4
#define KP_COL3 1<<5
#define KP_COL4 1<<6
#define KP_ROW1 1<<7
#define KP_ROW2 1<<8
#define KP_ROW3 1<<9
#define KP_ROW4 1<<10

#define KP_ROW_MASK (KP_ROW1 | KP_ROW2 | KP_ROW3 | KP_ROW4)
#define KP_COL_MASK (KP_COL1 | KP_COL2 | KP_COL3 | KP_COL4)

#define NUM_ROWS 4
#define NUM_COLS 4

/**
 *
 */
#define NO_KEY_PUSHED -1

/**
 * Define the non-numeric keys to have integer values from 10 to 15.
 */
enum specialKeys{
    A = 10,
    B,
    C,
    D,
    HASH,
    ASTERIX
};


/**
 * Initialise the ports need to use the keypad correctly.
 */
void keypadInitialise (void);

/**
 * Tell the getKeyPressed function that the key was accepted as a valid button.
 * This MUST be called with TRUE as an argument every time the getKeyPressed()
 * function is called and the key returned is accepted as a valid key for the
 * purpose.
 * This is because the getKeyPressed() function detects if the key has been held
 * down between presses so that multiple pushes aren't falsely detected. However
 * to get around the fact that the getKeyPressed() function is called from multiple
 * different places, when you call it you must specify that you then used this
 * key press so that the getKeyPressed can update the last key pressed.
 *
 * @param Bool Whether or not the key was accepted (generally always TRUE).
 */
void acceptedKey(bool);


/**
 * Get the key pressed on the keypad, if the key has been held down since the last
 * successful getKeyPressed() call, then this function returns NO_KEY_PUSHED.
 *
 * @return key The integer value of the key, or the specialKey value.
 */
int getKeyPressed (void);


#endif
