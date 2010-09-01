#ifndef _STDINC_H_
#define _STDINC_H_

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//   I N C L U D E S                                                         //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <stdbool.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//   C O N S T A N T S                                                       //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#define TICKS_PER_LOOP      100
#define TICKS_PER_SECOND    50000
#define LOOPS_PER_SECOND    500
#define LOOP_TIME_MS        2

// some constants may be needed in ram.h
#include "ram.h"

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//   M A C R O S                                                             //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#define HIGH(x)             ((uint8_t)((x) >> 8))
#define LOW(x)              ((uint8_t)(x))

#define MAX(a, b)           (((a) > (b)) ? (a) : (b))
#define MIN(a, b)           (((a) < (b)) ? (a) : (b))

#define LIMIT(x, min, max)  (((x) < (min)) ? (min) : (((x) < (max)) ? (x) : (max)))

#define PT1(new_val, old_val, time_constant_ms) \
    ((old_val) + ((new_val) - (old_val)) / ((time_constant_ms) / LOOP_TIME_MS))

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//   P R O T O T Y P E S                                                     //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

void init(void);

bool recvPacket(uint8_t *command, uint8_t *size, uint8_t **data);
void sendPacketBegin(uint8_t command);
void sendData(uint8_t byte);
void sendPacketEnd(void);

void input(void);
void output(void);

#endif // _STDINC_H_
