
#ifndef DFPLAYER_MINI_MP3_H
#define	DFPLAYER_MINI_MP3_H

#include <xc.h>
#include <stdint.h>
#include "Configuracion.h"
#include "UART.h"

typedef enum
{
    NONE_DFPLAY     = 0x00,
    PLAY_DFPLAYER   = 'A',
    PAUSE_DFPLAYER  = 'B',
    NEXT_DFPLAYER   = 'C',
    PREV_DFPLAYER   = 'D',
    RANDOM_DFPLAY   = 'E',
    VOL_DFPlayer    = 'V'     
}status_DFPlayer_t;

typedef enum
{
    DFP_NONE        = 0x00,
    DFP_NEXT        = 0x01,
    DFP_PREV        = 0x02,
    DFP_SET_VOL     = 0x06,
    DFP_PLAY        = 0x0D,
    DFP_PAUSE       = 0x0E,
    DFP_RANDOM      = 0x18
}mode_DFPlayer_t;

uint8_t cmd_DFPlayer[10] =
{
    0x7E,   // $S
    0xFF,   // VER
    0x06,   // LEN
    0x00,   // CMD
    0x00,   // FEEDBACK
    0x00,   // PARA 1
    0x00,   // PARA 2
    0x00,   // CHECKSUM
    0x00,   // CHECKSUM
    0xEF    // $0
};

void DFPlayer_Config(uint8_t *cmd_DFPlayer, mode_DFPlayer_t mode, uint8_t param1, uint8_t param2);

#endif	/* XC_HEADER_TEMPLATE_H */

