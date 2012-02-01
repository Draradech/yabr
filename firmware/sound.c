#include "stdinc.h"

#include "notes.h"
#include "sounds.h"

typedef struct
{
    bool playing;
    uint16_t index;
    uint8_t base;
    uint16_t to_next;
    uint8_t* sound;
    bool reset;
} PLAYER;

static PLAYER player;

void setSound(uint8_t num)
{
    if(num && !player.playing)
    {
        player.sound = (uint8_t*) pgm_read_word(&sounds[num - 1]);
        player.playing = true;
        DDRD |= (1 << PD5);
    }
}

static void soundReset(void)
{
    player.playing = false;
    player.index = 0;
    player.base = 80;
    player.to_next = 0;
    player.sound = (uint8_t*) 0;
    player.reset = 0;
    DDRD &= ~(1 << PD5);
}

static void soundUpdate(void)
{
    if(player.playing)
    {
        while(!player.reset && MODE(player.sound[player.index]) == CTRL)
        {
            if(COMMAND(player.sound[player.index]) == SETLENGTH)
            {
                player.index++;
                player.base = RAW(player.sound[player.index]);
                player.index++;
            }
            else if(COMMAND(player.sound[player.index]) == ENDOFARRAY)
            {
                player.reset = true;
            }
        }

        if(!player.reset && player.to_next == 1 && NOTE(player.sound[player.index]) != HOLD)
        {
            OCR1A = 0;
        }
        else if(player.to_next == 0)
        {
            if(player.reset)
            {
                soundReset();
                return;
            }

            if(NOTE(player.sound[player.index]) == HOLD)
            {
                ; // OCR1A = OCR1A
            }
            else if(NOTE(player.sound[player.index]) == PAUSE)
            {
                OCR1A = 0;
            }
            else
            {
                OCR1A = pgm_read_word(&cycles[NOTE(player.sound[player.index])]);
            }

            player.to_next = ((LENGTH(player.sound[player.index]) >> 6) + 1) * player.base;
            player.index++;
        }
        player.to_next--;
    }
}

void soundMain(void)
{
    if(attitude.voltage < 13000)
    {
        setSound(CRITBAT);
    }
    else if(attitude.voltage < 14000)
    {
        setSound(LOWBAT);
    }

    soundUpdate();
}
