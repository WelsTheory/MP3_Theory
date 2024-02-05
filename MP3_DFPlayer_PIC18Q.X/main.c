
#include <xc.h>
#include <stdint.h>
#include "Configuracion.h"
#include "INT.h"
#include "UART.h"
#include "DFPlayer.h"
    
extern volatile uint8_t BT_RX[1];
extern volatile uint8_t BT_VOL[2];
extern volatile uint8_t flag_DFP;
char data_BT;
extern volatile uint8_t flag_volumen;
extern volatile int8_t volumen;

status_DFPlayer_t status_DFPLAY = NONE_DFPLAY;

int main(void) {
    Clock_Init();
   
    TRISFbits.TRISF3 = 0; // salida
    ANSELFbits.ANSELF3 = 0; // Digital
    WPUFbits.WPUF3 = 0; // deshabilitado pull up
    INLVLFbits.INLVLF3 = 0; // TTL
    SLRCONFbits.SLRF3 = 1; // Limitado
    ODCONFbits.ODCF3 = 0; // Push Pull 
    
    TRISFbits.TRISF2 = 0; // salida
    ANSELFbits.ANSELF2 = 0; // Digital
    WPUFbits.WPUF2 = 0; // deshabilitado pull up
    INLVLFbits.INLVLF2 = 0; // TTL
    SLRCONFbits.SLRF2 = 1; // Limitado
    ODCONFbits.ODCF2 = 0; // Open 
    
    TRISFbits.TRISF5 = 0; // salida
    ANSELFbits.ANSELF5 = 0; // Digital
    WPUFbits.WPUF5 = 0; // deshabilitado pull up
    INLVLFbits.INLVLF5 = 0; // TTL
    SLRCONFbits.SLRF5 = 1; // Limitado
    ODCONFbits.ODCF5 = 0; // Open 
        
    UART_DFM_Init();
    UART_Init();
    INT_Init();
    
    __delay_ms(1000);
    DFPlayer_Config(&cmd_DFPlayer,DFP_SET_VOL,DFP_NONE,15);
    LATFbits.LATF2 = 1;
    while(1)
    {
        /* UART INTERRUPCIONES */
        if(flag_DFP)
        {
            status_DFPLAY = BT_RX[0];//A
            switch(status_DFPLAY)
            {
                case PLAY_DFPLAYER:
                    DFPlayer_Config(&cmd_DFPlayer,DFP_PLAY,DFP_NONE,DFP_NONE);
                    break;
                case PAUSE_DFPLAYER:
                    DFPlayer_Config(&cmd_DFPlayer,DFP_PAUSE,DFP_NONE,DFP_NONE);
                    break;
                case NEXT_DFPLAYER:
                    DFPlayer_Config(&cmd_DFPlayer,DFP_NEXT,DFP_NONE,DFP_NONE);
                    break;
                case PREV_DFPLAYER:
                    DFPlayer_Config(&cmd_DFPlayer,DFP_PREV,DFP_NONE,DFP_NONE);
                    break;
                case VOL_DFPlayer:
                    DFPlayer_Config(&cmd_DFPlayer,DFP_SET_VOL,DFP_NONE,(int8_t)(((BT_VOL[0]&0x0F)<<4) | ((BT_VOL[1]&0X0f)))); 
                    break;
                case RANDOM_DFPLAY:
                    DFPlayer_Config(&cmd_DFPlayer,DFP_RANDOM,DFP_NONE,DFP_NONE);
                default:
                    //DFPlayer_Folder_Pista(1,1);
                    break;           
            }
            flag_DFP = 0;
        }    
        /* INTERRUPCIONES */
        if(flag_volumen)
        {
            DFPlayer_Config(&cmd_DFPlayer, DFP_SET_VOL, DFP_NONE, volumen);
            flag_volumen = 0;
        }  
    }
    return 0;
}

