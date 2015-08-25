/**
 * @file kernel.c
 * @version 01.06.2011
 * @authors Aydin Arik, Kevin Doran, Tim Grunshaw
 *
 * Contains the kernel that runs the Home Automation System. Including task
 * scheduler, time keeping, state control and four general purpose functions
 * needed by the kernel to operate correctly.
 */

// Include Standard files
#include "Board.h"
#include "clock.h"
#include "display.h"
#include "input.h"
#include "TC_PWM.h"
#include "boolean.h"
#include "led.h"
#include "tasks.h"
#include "state.h"
#include "timers.h"
#include "kernel.h"


bool* timerMatch;
volatile time_t theTime = {0,1}; // 1 minute late so that all the timers don't start immediately.

/**
 * Upon changing states a label is briefly displayed (~1s) indicating what
 * state the user has just entered.
 *
 * These variables are needed to keep track of state changes, display time &
 * how long the label has been displayed.
 */
int lastState;
const int maxWait = 8000;
int wait = 0;


void run(void)
{
    /*
     * Initialise functions.
     */
	clockInitialise();
	ledInitialise();
	displayInitialise();
    keypadInitialise();
    soundInitialise();

    /*
     * Start in NORMAL state.
     */
    state = NORMAL;


    // Main loop
	while(TRUE)
	{

		// Check clock.
		clockPause();
		if(clockCheck())
		{
			clockIncrement(&theTime);
		}


		// Run any tasks that have reached their time to be run.
		timerMatch = checkTimers(&theTime, timers);
		int i;
		for(i = 0; i < NUM_TIMERS; i++)
		{
		    if(timerMatch[i])
		    {
		        (*timerTasks[i]) ();
		    }
		}

		// Run any none timer tasks which are active.
		for(i = 0; i < NUM_NON_TIMER_TASKS; i++)
		{
		    if(nonTimerTaskActive[i])
		    {
		        (*nonTimerTasks[i]) (&theTime);
		    }
		}


		// Changes the state if a button is pressed.
		checkState();


		// Go into the desired state.
		switch (state)
		{
		case NORMAL:
			normalState(&theTime);
			lastState = state;
			break;
		case AUTHORISED:
		    if((state != lastState))
            {
                if (waitWithMessage("AUtH"))
                    break;
            }
		    authorisedState(&theTime);
		    lastState = state;
		    wait = 0;
		    break;
		case LOG_OUT:
		    logOutState();
		    lastState = state;
		    break;
		case CLOCK_ADJUST:
            if((state != lastState))
            {
                if (waitWithMessage("t AJ"))
                    break;
            }
		    wait = 0;
		    lastState = state;
			clockAdjustState(&theTime);
			break;
		case SET_TIMER_1_START:
            if((state != lastState))
            {
                if (waitWithMessage("t1 S"))
                    break;
            }
		    wait = 0;
		    lastState = state;
		    setTimer1StartState();
		    break;
		case SET_TIMER_1_END:
            if((state != lastState))
            {
                if (waitWithMessage("t1 E"))
                    break;
            }
            wait = 0;
            lastState = state;
		    setTimer1EndState();
		    break;
		case SET_TIMER_2_START:
            if((state != lastState))
            {
                if (waitWithMessage("t2 S"))
                    break;
            }
            wait = 0;
            lastState = state;
		    setTimer2StartState();
		    break;
		case SET_TIMER_2_END:
            if((state != lastState))
            {
                if (waitWithMessage("t2 E"))
                    break;
            }
            wait = 0;
            lastState = state;
		    setTimer2EndState();
		    break;
		case SET_ALARM:
            if((state != lastState))
            {
                if (waitWithMessage("A   "))
                    break;
            }
            lastState = state;
            wait = 0;
		    setAlarmState();
		    break;
	      case CONFIRM_SET:
	          if((state != lastState))
	          {
	              if(waitWithMessage("tCon"))
	                  break;
	          }

	            lastState = state;
	            wait = 0;
	            confirmSetState();
	            break;
	      case INPUT_PASSWORD:
	          if((state != lastState))
	          {
	              if (waitWithMessage("Ent "))
	                  break;
	          }
            lastState = state;
            wait = 0;
            inputPasswordState();
            break;
	      case ADD_USER:
	           if(state != lastState)
	              {
	                  if (waitWithMessage("USE "))
	                      break;
	              }
	            lastState = state;
	            wait = 0;
	            addUserState();
	            break;
	      case AUTOMATED_LIGHT_SYSTEM:
	          if(nonTimerTaskActive[CHECK_LIGHTS])
              {
                  if(waitWithMessage("OFF "))
                        break;
                  nonTimerTaskActive[CHECK_LIGHTS] = FALSE;
              }
              else
              {
                  if(waitWithMessage("On  "))
                        break;
                  nonTimerTaskActive[CHECK_LIGHTS] = TRUE;
              }
	          lastState = state;
	          wait = 0;
	          state = AUTHORISED; // Just go to authorised.
	          break;
	      case ALARM_STATE:
	          lastState = state;
	          alarmState();
	          break;
		}
	}
}


/*
 *
 */
bool waitWithMessage(char* string)
{
    displayString(string);
    while(wait++ < maxWait)
    {
        return TRUE;
    }
    return FALSE;

}

/*
 * Case A:
 * clock_adjust --> timer1_start --> timer1_end --> timer2_start --> timer2_end
 *              --> alarm
 */
void checkState()
{
	int key = getKeyPressed();

	switch (key)
	{
	case A:
	    if(state == AUTHORISED) // Only change into clock adjusting states if in normal.
	    {
            state = CLOCK_ADJUST;
            acceptedKey(TRUE);
	    }
	    else
	    {
	        // Ignore press if not in normal state.
	    }
	    break;
	case B:
        if (state == NORMAL)
        {
            state = INPUT_PASSWORD;
            acceptedKey(TRUE);
        }
        else if(state == AUTHORISED)
        {
            state = ADD_USER;
            acceptedKey(TRUE);
        }
        else if(state == ADD_USER)
        {
            state = LOG_OUT;
            acceptedKey(TRUE);
        }
        else
        {
            // Ignore press if not in normal state.
        }
        break;
	case C:
	    if(state == AUTHORISED)
	    {
	        state = AUTOMATED_LIGHT_SYSTEM;
	        acceptedKey(TRUE);
	    }
	    else
	    {
	        // Ignore press if not in normal state.
	    }
	    break;
	case D:
	    /*
	     * If in any state other than normal, inputing the password or Alarm,
	     * then must be authorised so go back to authorised.
	     */
	    if(state == INPUT_PASSWORD || state == ALARM_STATE)
	    {
	        state = NORMAL;
	        acceptedKey(TRUE);
	    }
	    else if(state != NORMAL)
	    {
	        state = AUTHORISED;
	        acceptedKey(TRUE);
	    }
		break;
	case ASTERIX: // Cycle through clock adjust states.
	    // If in a timer adjust mode
	    if(state == CLOCK_ADJUST || state == SET_TIMER_1_START
	            || state == SET_TIMER_1_END || state == SET_TIMER_2_START
	            || state == SET_TIMER_2_END || state == SET_ALARM)
	    {
	        if(state == SET_ALARM) // End state, cycle back to first state.
	        {
	            state = CLOCK_ADJUST; // First clock adjust state.
	        }
	        else
	        {
	            state++; // Clock adjust states are sequential so can simply go to next state.
	        }
	        acceptedKey(TRUE);
	    }
	    else
	    {
           // Do nothing if not in timer adjust state.
	    }
        break;
	default:
		break; /* Stay in current state */
	}
}


/*
 *
 */
void flashClockDisplay(time_t* const time)
{
    static int flash = 0;

    flash++;
    if(flash > 750)
    {
        displayTime(time);
        if(flash > 1500)
            flash = 0;
    }
    else
    {
        displayNum(-1, 0, 0);
    }
}


/*
 *
 */
bool adjustTime(time_t* timeToAdjust, int* currentDigit)
{
    flashClockDisplay(timeToAdjust);

    // Checks to see if hash was pressed, i.e. time has been finished set.
    bool hashPress = FALSE;

    int key = getKeyPressed();

    if(key == NO_KEY_PUSHED)
    {
        return FALSE;
    }
    else
    {
        bool isTimeLessThan24;

        switch (*currentDigit)
        {
        case 0:
            if(key >= 0 && key <= 2)
            {
                timeToAdjust->hours = key * 10;
                (*currentDigit)++;
                acceptedKey(TRUE);
            }
            else if (key == HASH)/*Zeroing clock instantly */
            {
                hashPress = TRUE;
                // Reset the state of the clock adjuster.
                (*currentDigit) = 0;
                acceptedKey(TRUE);
            }
            break;
        case 1:
            isTimeLessThan24 = ((timeToAdjust->hours != 20) || (key >= 0 && key <= 3));
            if(key >= 0 && key <= 9 && isTimeLessThan24)
            {
                timeToAdjust->hours += key;
                (*currentDigit)++;
                acceptedKey(TRUE);
            }
            else if (key == HASH)/*Shortcut to set last three clock digits to zero. e.g. X0.00, where X is a number entered. */
            {
                hashPress = TRUE;
                // Reset the state of the clock adjuster.
                (*currentDigit) = 0;
                acceptedKey(TRUE);
            }
            break;
        case 2:
            if(key >= 0 && key <= 5)
            {
                timeToAdjust->minutes = key * 10;
                (*currentDigit)++;
                acceptedKey(TRUE);
            }
            else if (key == HASH)/*Shortcut to set last two clock digits to zero. e.g. XY.00, where X and Y are numbers entered. */
            {
                hashPress = TRUE;
                // Reset the state of the clock adjuster.
                (*currentDigit) = 0;
                acceptedKey(TRUE);
            }
            break;
        case 3:
            if(key >= 0 && key <= 9)
            {
                timeToAdjust->minutes += key;
                (*currentDigit)++;
                acceptedKey(TRUE);
            }
            else if (key == HASH) /*Shortcut to set last clock digit to zero. e.g. XY.Z0, where X, Y and Z are numbers entered. */
            {
                hashPress = TRUE;
                // Reset the state of the clock adjuster.
                (*currentDigit) = 0;
                acceptedKey(TRUE);
            }
            break;
        case 4:   //The full time has been inputed. It can now be saved.
            if(key == HASH)//confirm clock time chosen
            {
                hashPress = TRUE;
                // Reset the state of the clock adjuster.
                (*currentDigit) = 0;
                acceptedKey(TRUE);
            }
            break;
        }

        return hashPress;
    }
}
