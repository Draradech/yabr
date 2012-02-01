#ifndef _NOTES_H_
#define _NOTES_H_

#define C2 0
#define Cx2 1
#define Db2 1
#define D2 2
#define Dx2 3
#define Eb2 3
#define E2 4
#define F2 5
#define Fx2 6
#define Gb2 6
#define G2 7
#define Gx2 8
#define Ab2 8
#define A2 9
#define Ax2 10
#define B2 10
#define H2 11
#define C3 12
#define Cx3 13
#define Db3 13
#define D3 14
#define Dx3 15
#define Eb3 15
#define E3 16
#define F3 17
#define Fx3 18
#define Gb3 18
#define G3 19
#define Gx3 20
#define Ab3 20
#define A3 21
#define Ax3 22
#define B3 22
#define H3 23
#define C4 24
#define Cx4 25
#define Db4 25
#define D4 26
#define Dx4 27
#define Eb4 27
#define E4 28
#define F4 29
#define Fx4 30
#define Gb4 30
#define G4 31
#define Gx4 32
#define Ab4 32
#define A4 33
#define Ax4 34
#define B4 34
#define H4 35
#define C5 36
#define Cx5 37
#define Db5 37
#define D5 38
#define Dx5 39
#define Eb5 39
#define E5 40
#define F5 41
#define Fx5 42
#define Gb5 42
#define G5 43
#define Gx5 44
#define Ab5 44
#define A5 45
#define Ax5 46
#define B5 46
#define H5 47
#define C6 48
#define Cx6 49
#define Db6 49
#define D6 50
#define Dx6 51
#define Eb6 51
#define E6 52
#define F6 53
#define Fx6 54
#define Gb6 54
#define G6 55
#define Gx6 56
#define Ab6 56
#define A6 57
#define Ax6 58
#define B6 58
#define H6 59

#define PAUSE 61
#define HOLD 62
#define CTRL 63

#define LENGTH(note) (pgm_read_byte(&note) & 0xC0)
#define NOTE(note) (pgm_read_byte(&note) & 0x3F)
#define COMMAND(note) (pgm_read_byte(&note) & 0xC0)
#define MODE(note) (pgm_read_byte(&note) & 0x3F)
#define RAW(note) (pgm_read_byte(&note))

#define L1 (0 << 6)
#define L2 (1 << 6)
#define L3 (2 << 6)
#define L4 (3 << 6)

#define ENDOFARRAY (0 << 6)
#define SETLENGTH (1 << 6)

extern PROGMEM uint16_t cycles[];

#endif // _NOTES_H_