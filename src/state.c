/**
 * @file state.c
 * @version 01.06.2011
 * @authors Aydin Arik, Kevin Doran, Tim Grunshaw
 *
 * Contains the states of the Home Automation System program. Each state is a
 * small function that is called repetitively by the kernel until a state change
 * occurs. Because each state has a independent sequence of operations and
 * decisions, the effective result when called many times is that the
 * microcontroller appears to be in a different state.
 *
 * This file also contains some variable and small routines needed by one or more
 * of the states.
 */

#include "state.h"
#include "kernel.h"
#include "tasks.h"
#include "boolean.h"
#include "input.h"
#include "display.h"
#include "ir_sensor.h"
#include "Board.h"
#include "tasks.h"

/**
 * Holds all possible passwords. There can be max of 10.
 * The master password is 1111.
 */
int allPasswords[10][4] = {
                         {1, 1, 1, 1},    {-1, -1, -1, -1},
                         {-1, -1, -1, -1},{-1, -1, -1, -1},
                         {-1, -1, -1, -1},{-1, -1, -1, -1},
                         {-1, -1, -1, -1},{-1, -1, -1, -1},
                         {-1, -1, -1, -1},{-1, -1, -1, -1}
};


/**
 * Set to only 1 to begin with. This is so that users can't
 *  accidentally match a password not set.
 */
int numPasswords = 1;


/*
 *
 */
void normalState(time_t* const theTime)
{
    displayTime(theTime);
}


/*
 *
 */
void authorisedState(time_t* const theTime)
{
    normalState(theTime); // This is a dummy function to allow for future expansion.
}


/*
 *
 */
void logOutState()
{
    int key = getKeyPressed();

    displayString("HASH");

    if(key == HASH)
    {
        state = NORMAL; // Just go back to normal state again.
        acceptedKey(TRUE);
    }
    else if(key == ASTERIX) // Use asterix to reset whole system.
    {
        // Reset passwords.
        numPasswords = 1;

        int i;

        // Reset timers.
        for(i = 0; i < NUM_TIMERS; i++)
        {
            timers[i]->hours = 0;
            timers[i]->minutes = 0;
        }

        state = NORMAL;
        acceptedKey(TRUE);
    }

}


/*
 *
 */
void clockAdjustState(time_t* currentTime)
{
    static time_t adjustedTime = {0, 0};
    static int currentDigit = 0;


    if(adjustTime(&adjustedTime, &currentDigit))
    {
        currentTime->hours = adjustedTime.hours;
        currentTime->minutes = adjustedTime.minutes;
        adjustedTime.hours = 0;
        adjustedTime.minutes = 0;
        state = AUTHORISED;
    }
}


/*
 *
 */
void setTimer1StartState()
{
    static time_t adjustedTime = {0, 0};
    static int currentDigit = 0;

    if(adjustTime(&adjustedTime, &currentDigit))
    {
        timer1Start.hours = adjustedTime.hours;
        timer1Start.minutes = adjustedTime.minutes;
        adjustedTime.hours = 0;
        adjustedTime.minutes = 0;
        state = CONFIRM_SET;
    }
}


/*
 *
 */
void setTimer1EndState()
{
    static time_t adjustedTime = {0, 0};
    static int currentDigit = 0;

    if(adjustTime(&adjustedTime, &currentDigit))
    {
        timer1End.hours = adjustedTime.hours;
        timer1End.minutes = adjustedTime.minutes;
        adjustedTime.hours = 0;
        adjustedTime.minutes = 0;
        state = CONFIRM_SET;
    }

}


/*
 *
 */
void setTimer2StartState()
{
    static time_t adjustedTime = {0, 0};
    static int currentDigit = 0;

    if(adjustTime(&adjustedTime, &currentDigit))
    {
        timer2Start.hours = adjustedTime.hours;
        timer2Start.minutes = adjustedTime.minutes;
        adjustedTime.hours = 0;
        adjustedTime.minutes = 0;
        state = CONFIRM_SET;
    }
}


/*
 *
 */
void setTimer2EndState()
{
    static time_t adjustedTime = {0, 0};
    static int currentDigit = 0;

    if(adjustTime(&adjustedTime, &currentDigit))
    {
        timer2End.hours = adjustedTime.hours;
        timer2End.minutes = adjustedTime.minutes;
        adjustedTime.hours = 0;
        adjustedTime.minutes = 0;
        state = CONFIRM_SET;
    }
}


/*
 *
 */
void setAlarmState()
{
    static time_t adjustedTime = {0, 0};
    static int currentDigit = 0;

    if(adjustTime(&adjustedTime, &currentDigit))
    {
        timerAlarm.hours = adjustedTime.hours;
        timerAlarm.minutes = adjustedTime.minutes;
        adjustedTime.hours = 0;
        adjustedTime.minutes = 0;
        state = CONFIRM_SET;
    }
}


/*
 *
 */
void alarmState()
{
    static unsigned int count = 0;

    displayString("AL  "); // Display AL for alarm.

    count++;

    if(count > TWENTY_SECONDS)
    {
        state = NORMAL;
        turnOffAlarmTask();
        count = 0;
    }
}


/*
 * Gives feedback on whether time was successfully set.
 */
void confirmSetState()
{
    state = CLOCK_ADJUST;
}


/*
 *
 */
void inputPasswordState()
{
    static int currentDigit = 0;
    static int enteredPassword[PASSWORD_LENGTH] = {-1, -1, -1, -1};

    static bool hasFailed = FALSE;

    int passwordValueTyped = getKeyPressed();

    displayIntString(enteredPassword);

    if(hasFailed)
    {
        displayString("FAIL");
    }

    if(passwordValueTyped >= 0 && passwordValueTyped <= 9 && currentDigit < PASSWORD_LENGTH)
    {
        hasFailed = FALSE;
        acceptedKey(TRUE);

        // Display key just pressed. (Numeric only)
        //displayNum(passwordValueTyped, currentDigit, 0);



        enteredPassword[currentDigit] = passwordValueTyped;

        currentDigit++;
    }
    else if(passwordValueTyped == HASH)
    {
        currentDigit = 0;
        acceptedKey(TRUE);

        if (comparePasswords(enteredPassword)) // Success
        {
           hasFailed = FALSE;
           state = AUTHORISED;
        }
        else
        {
            hasFailed = TRUE;
        }

        int i;
        for(i = 0; i < PASSWORD_LENGTH; i++)
        {
            enteredPassword[i] = -1;
        }

    }
}


/*
 *
 */
bool comparePasswords(int* enteredPassword)
{
    int i, j;
    // Cycle through passwords
    for(i = 0; i < numPasswords; i++)
    {
        // Check each letter of each password.
        for(j = 0; j < PASSWORD_LENGTH; j++)
        {
            if(allPasswords[i][j] != enteredPassword[j])
                break;

            if(j == 3) // A password has been matched if j got to this.
                return TRUE;
        }
    }
    return FALSE;
}


/*
 *
 */
void addUserState()
{
    // Just display no if all the users have been added.
    if(numPasswords == MAX_USERS)
    {
        displayString("nO  ");
        return;
    }


    static int currentDigit = 0;
    static int newPassword[PASSWORD_LENGTH] = {-1, -1, -1, -1}; // Blank state.

    int i;

    int key = getKeyPressed();

    displayIntString(newPassword);

    if(key >= 0 && key <= 9 && currentDigit < PASSWORD_LENGTH)
    {
        acceptedKey(TRUE);
        newPassword[currentDigit] = key;
        currentDigit++;
    }
    else if(key == HASH)
    {
        acceptedKey(TRUE);

        // If password is fully entered then add it to the passwords array.
        if(currentDigit == 4)
        {
            for(i = 0; i < PASSWORD_LENGTH; i++)
            {
                allPasswords[numPasswords][i] = newPassword[i];
            }

            // Increment the numPasswords.
            numPasswords++;

            // Go back to the authorised state.
            state = AUTHORISED;
        }

        currentDigit = 0;

        // reset new password
        for(i = 0; i < PASSWORD_LENGTH; i++)
        {
            newPassword[i] = -1;
        }
    }
}
