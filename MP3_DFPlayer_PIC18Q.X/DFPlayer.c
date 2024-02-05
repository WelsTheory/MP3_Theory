
#include "DFPlayer.h"

static void Send_Data_DFPlayer(uint8_t *cmd_DFPlayer)
{
    uint16_t checksum = 0;
    uint8_t i;
    for(i=1; i<7; i++)
    { 
        checksum += cmd_DFPlayer[i];
    } 
    checksum = -checksum ;
    cmd_DFPlayer[7] = (uint8_t)((checksum&0xFF00)>> 8);
    cmd_DFPlayer[8] = (uint8_t)checksum&0x00FF;       
    for(i=0;i<10;i++)
    {          
        DFM_Tx(cmd_DFPlayer[i]);
        //UART_Tx(cmd[i]); 
    }
    __delay_ms(1); 
}

void DFPlayer_Config(uint8_t *cmd_DFPlayer, mode_DFPlayer_t mode, uint8_t param1, uint8_t param2)
{
    cmd_DFPlayer[3] = mode;
    cmd_DFPlayer[5] = param1;
    cmd_DFPlayer[6] = param2;
    Send_Data_DFPlayer(cmd_DFPlayer);
}



