/**
 * @file input.c
 * @version 01.06.2011
 * @authors Aydin Arik, Kevin Doran, Tim Grunshaw
 *
 * Contains functions needed to use the keypad correctly.
 */

#include "input.h"
#include "Board.h"
#include "boolean.h"

static int key = NO_KEY_PUSHED;
static int lastKey = NO_KEY_PUSHED;

int keyValue[NUM_ROWS][NUM_COLS] = {
    { 1, 2, 3, A },
    { 4, 5, 6, B },
    { 7, 8, 9, C },
    { ASTERIX, 0, HASH, D }
};

unsigned int KPRowMat[] = {
    KP_ROW1,
    KP_ROW2,
    KP_ROW3,
    KP_ROW4
};

unsigned int KPColMat[] = {
    KP_COL1,
    KP_COL2,
    KP_COL3,
    KP_COL4
};

void keypadInitialise (void)
{
    AT91F_PIO_CfgOutput( AT91C_BASE_PIOA, KP_ROW_MASK) ;
    AT91F_PIO_ClearOutput( AT91C_BASE_PIOA, KP_ROW_MASK) ;
}


void acceptedKey(bool accepted)
{
    if(accepted)
    {
       lastKey = key;
    }
}

int getKeyPressed (void)
{
        int i, j;
        int row = NO_KEY_PUSHED, col = NO_KEY_PUSHED;

        // A key is noticed to be pressed when a column input=0. To find the specific key pressed, make a row output=1 to get column input=1.
        for (i = 0; i < NUM_COLS; i++) // Iterating through each key column
        {
            if ((AT91F_PIO_GetInput(AT91C_BASE_PIOA) & KPColMat[i]) == 0) // Has a key been pressed?
            {
                col = i;
                for (j = 0; j < NUM_ROWS; j++) // Iterating through each key column again to find out which key is pressed
                {
                    AT91F_PIO_SetOutput( AT91C_BASE_PIOA,  KPRowMat[j]) ; // setting a row output for the 'test'

                    if ((AT91F_PIO_GetInput(AT91C_BASE_PIOA) & KPColMat[i]) != 0) // if the column input is high, then 'this' key was pressed
                    {
                        row = j;
                        AT91F_PIO_ClearOutput( AT91C_BASE_PIOA,  KPRowMat[j]) ; // reset test output
                        break;
                    }
                    else
                    {
                        AT91F_PIO_ClearOutput( AT91C_BASE_PIOA,  KPRowMat[j]) ;// reset test output
                    }
                }
            }
        }

    if ( (row == NO_KEY_PUSHED) || (col == NO_KEY_PUSHED) ) // no keys are pressed
    {
        key = NO_KEY_PUSHED;
        lastKey = NO_KEY_PUSHED; // Set lastKey to no key so that it can be
                                // detected if a button is pressed twice.
    }

    else // a key is pressed
    {
        key = keyValue[row][col];
        if(key == lastKey)
        {
            // Send NO_KEY_PUSHED to indicate that key is held.
            key = NO_KEY_PUSHED;
        }
    }
    return key;
}
