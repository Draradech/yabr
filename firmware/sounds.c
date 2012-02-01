#include "stdinc.h"

#include "notes.h"
#include "sounds.h"

//################################################
PROGMEM static uint8_t lowbat[]  =
{
    CTRL    | SETLENGTH,
    40,

    C4  | L1,
    PAUSE   | L3,
    PAUSE   | L4,

    PAUSE   | L4,
    PAUSE   | L4,

    PAUSE   | L4,
    PAUSE   | L4,

    CTRL | ENDOFARRAY
};

//################################################
PROGMEM static uint8_t critbat[]  =
{
    CTRL | SETLENGTH,
    120,

    A4  | L4,
    D5 | L4,

    CTRL | ENDOFARRAY
};

//################################################
PROGMEM static uint8_t disable[]  =
{
    CTRL | SETLENGTH,
    60,

    C4  | L2,
    G3  | L2,
    E3  | L2,
    C3  | L4,

    CTRL | ENDOFARRAY
};

//################################################
PROGMEM static uint8_t enable[]  =
{
    CTRL | SETLENGTH,
    60,

    C3  | L2,
    E3  | L2,
    G3  | L2,
    C4  | L4,

    CTRL | ENDOFARRAY
};

//################################################
PROGMEM uint8_t* sounds[] =
{
    lowbat,
    critbat,
	 disable,
	 enable
};
