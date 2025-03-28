#ifndef _SYSTEMCONSTS_H_
#define _SYSTEMCONSTS_H_

// System-level constants.

// Keys.
/*
 0  1 2  3
 7  6 5  4
*/ 

// LEDs - actually the same as Keys.
/*
 0  1 2  3
 7  6 5  4
*/ 

enum class SystemLedID
{
    LEFT_UP_LED = 0,
    MENU_PREV_LED = 1,
    MENU_NEXT_LED = 2,
    RIGHT_UP_LED = 3,

    RIGHT_DOWN_LED = 4,
    MENU_OK_LED = 5,
    MENU_CANCEL_LED = 6,
    LEFT_DOWN_LED = 7
};

// Displays
// LEFT  CENTER  RIGHT
enum class SystemDisplayID
{
    LEFT_DISPLAY = 0,
    CENTER_DISPLAY = 1,
    RIGHT_DISPLAY = 2
};

#endif //_SYSTEMCONSTS_H_