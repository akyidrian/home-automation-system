/**
 * @file display.c
 * @version 01.06.2011
 * @authors Aydin Arik, Kevin Doran, Tim Grunshaw
 *
 * Contains functions needed to use the 7 segment display to show characters.
 */

#include "display.h"
#include "Board.h"
#include "boolean.h"


void displayInitialise()
{
	/* No need to set these pins to be driven by the PIO because it is GPIO pins only.
        Set 7-Seg display to all off.
    */
	AT91F_PIO_CfgOutput( AT91C_BASE_PIOA, (DIG_MASK | FULL_ON) ) ;
}


/*
 *
 */
void displayNum(int num, int dig, bool decimal)
{
    int number;
    int digit;

    switch (num)
    {
        case 0:
            number = ZERO;
            break;
        case 1:
            number = ONE;
            break;
        case 2:
            number = TWO;
            break;
        case 3:
            number = THREE;
            break;
        case 4:
            number = FOUR;
            break;
        case 5:
            number = FIVE;
            break;
        case 6:
            number = SIX;
            break;
        case 7:
            number = SEVEN;
            break;
        case 8:
            number = EIGHT;
            break;
        case 9:
            number = NINE;
            break;
        case '0':
             number = ZERO;
             break;
         case '1':
             number = ONE;
             break;
         case '2':
             number = TWO;
             break;
         case '3':
             number = THREE;
             break;
         case '4':
             number = FOUR;
             break;
         case '5':
             number = FIVE;
             break;
         case '6':
             number = SIX;
             break;
         case '7':
             number = SEVEN;
             break;
         case '8':
             number = EIGHT;
             break;
         case '9':
             number = NINE;
             break;
        case 'A':
            number = LETTER_A;
            break;
        case 'C':
            number = LETTER_C;
            break;
        case 'E':
            number = LETTER_E;
            break;
        case 'F':
            number = LETTER_F;
            break;
        case 'H':
            number = LETTER_H;
            break;
        case 'I':
            number = LETTER_I;
            break;
        case 'J':
            number = LETTER_J;
            break;
        case 'L':
            number = LETTER_L;
            break;
        case 'S':
            number = LETTER_S;
            break;
        case 'n':
            number = LETTER_n;
            break;
        case 'o':
            number = LETTER_o;
            break;
        case 'O':
            number = LETTER_O;
            break;
        case 'P':
            number = LETTER_P;
            break;
        case 't':
            number = LETTER_t;
            break;
        case 'U':
            number = LETTER_U;
            break;
        case -1:
            number = BLANK;
            break;
        default:
            number = BLANK;
            break;
    }

    switch (dig)
    {
        case 0:
            digit = DIG0;
            break;
        case 1:
            digit = DIG1;
            break;
        case 2:
            digit = DIG2;
            break;
        case 3:
            digit = DIG3;
            break;
    }

    if(decimal)
    {
        number |= DOT;
    }

    AT91F_PIO_SetOutput( AT91C_BASE_PIOA,  DIG_MASK | FULL_ON) ;
    AT91F_PIO_ClearOutput( AT91C_BASE_PIOA, digit | number) ;
}


/*
 *
 */
void displayString(char* string)
{
    static unsigned int digit = 0;

    switch (digit)
    {
    case 0:
        displayNum(string[0], 0, FALSE);
        break;
    case 1:
        displayNum(string[1], 1, FALSE);
        break;
    case 2:
        displayNum(string[2], 2, FALSE);
        break;
    case 3:
        displayNum(string[3], 3, FALSE);
        break;
    }
    // Loop around
    digit = (digit > 2) ? 0 : digit + 1;
}


/*
 *
 */
void displayIntString(int intString[])
{
    static unsigned int digit = 0;

     switch (digit)
     {
     case 0:
         displayNum(intString[0], 0, FALSE);
         break;
     case 1:
         displayNum(intString[1], 1, FALSE);
         break;
     case 2:
         displayNum(intString[2], 2, FALSE);
         break;
     case 3:
         displayNum(intString[3], 3, FALSE);
         break;
     }
     // Loop around
     digit = (digit > 2) ? 0 : digit + 1;
}


/*
 *
 */
void displayTime(time_t* time)
{
    static unsigned int digit = 0;
    int num;

    switch (digit)
    {
    case 0:
        num = (time->hours) / 10;
        displayNum(num, 0,FALSE);
        break;
    case 1:
        num = (time->hours) % 10;
        displayNum(num, 1,TRUE);
        break;
    case 2:
        num = (time->minutes) / 10;
        displayNum(num, 2,FALSE);
        break;
    case 3:
        num = (time->minutes) % 10;
        displayNum(num, 3,FALSE);
        break;
    }
    // Loop around
    digit = (digit > 2) ? 0 : digit + 1;
}
