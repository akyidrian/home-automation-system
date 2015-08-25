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

#ifndef STATE_H_
#define STATE_H_

#include "clock.h"
#include "boolean.h"

/**
 *  Approximately 60000 iterations of the ALARM_STATE
 */
#define TWENTY_SECONDS 60000

/**
 * The number of users that can be added to the Home Automation System.
 */
#define MAX_USERS 10


/**
 * The length of a password.
 */
#define PASSWORD_LENGTH 4


/**
 * Enumeration of the possible states that the HAS could be in.
 */
enum states{NORMAL = 0, AUTHORISED, LOG_OUT, CLOCK_ADJUST, SET_TIMER_1_START,
    SET_TIMER_1_END,SET_TIMER_2_START, SET_TIMER_2_END, SET_ALARM, CONFIRM_SET,
    ADD_USER,INPUT_PASSWORD, AUTOMATED_LIGHT_SYSTEM, ALARM_STATE};


/**
 * Normal state displays the system time. It allows you to enter the password
 * input state, but no other state can be entered while in normal state. The
 * buttons will do nothing.
 *
 * @param time The current system time.
 */
void normalState(time_t* const);


/**
 * Authorised state is the default state once the user has entered a correct
 * password. The system time is displayed when in this state, and upon entering
 * this state, "AUtH" is briefly displayed to notify the user that they are
 * in the authorised state.
 * All other states can be entered from the authorised state, including adjusting
 * the system time, the timers, the alarm, and the add new users state.
 * The user can log out of the authorised state by pressing B twice to enter the
 * log out state, then HASH to confirm.
 *
 * @param time The current system time.
 */
void authorisedState(time_t* const);


/**
 * Log out state is a small state which allows an authorised user to log out back
 * into normal state by pressing HASH. The display shows "HASH" to instruct the
 * user what to do.
 * The user could also press the asterix symbol while in this state to RESET the
 * whole system back to 'manufacturers state'. All passwords will be wiped except
 * the default one, and all timers reset to 00:00.
 */
void logOutState(void);


/**
 * Clock adjust state allows the user to adjust the system clock. It flashes the
 * time they want to adjust to, and when the user presses hash the system time
 * is set the adjusted time.
 *
 * @param time The system time.
 */
void clockAdjustState(time_t*);


/**
 * This state allows the user to adjust the timer 1 start time.
 */
void setTimer1StartState(void);


/**
 * This state allows the user to adjust the timer 1 end time.
 */
void setTimer1EndState(void);


/**
 * This state allows the user to adjust the timer 2 start time.
 */
void setTimer2StartState(void);


/**
 * This state allows the user to adjust the timer 2 end time.
 */
void setTimer2EndState(void);


/**
 * This state allows the user to adjust the alarm timer.
 */
void setAlarmState(void);


/**
 * This is a very brief (1s) state that displays a message confirming that the user
 * has successfully set a timer by displaying "tCon" for time confirmed.
 */
void confirmSetState(void);


/**
 * This state allows an authorised user to add new passwords for new users. Up to
 * 10 of these passwords may be added. Again the numeric password is typed, and
 * the user presses hash to confirm.
 */
void addUserState(void);


/**
 * This is the state where a user in normal state can enter a password to enter
 * an authorised state. Once the user has entered a 4 digit password, they press
 * hash to confirm. If the password is incorrect the display will display "FAIL",
 * and give the user an opportunity to try again. Upon success the display will
 * display "PASS" and the authorised state will be entered.
 */
void inputPasswordState(void);


/**
 * During this state the alarm will sound the display will show "AL" for alarm.
 * This state is entered when the alarm timer is matched, and will continue for
 * 20 seconds. At anytime the user can press the normal D cancel key to stop the
 * alarm.
 */
void alarmState(void);


/**
 * This is a routine used by the inputPasswordState to determine if the entered
 * password matched any of the authorised user passwords.
 *
 * @return TRUE if successful.
 */
bool comparePasswords(int*);

#endif /* STATE_H_ */
