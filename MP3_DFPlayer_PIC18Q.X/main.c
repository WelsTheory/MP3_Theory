
#include <xc.h>
#include <stdint.h>
#include "Configuracion.h"
#include "INT.h"
#include "UART.h"
#include "DFPlayer.h"
#include "SSD1306.h"
#include "I2C.h"
#include "Text_Font.h"
#include "Cancion_Index.h"
    
extern volatile uint8_t BT_RX[1];
extern volatile uint8_t BT_VOL[2];
extern volatile uint8_t flag_DFP;
char data_BT;
extern volatile uint8_t flag_volumen;
extern volatile int8_t volumen;

extern volatile uint8_t BT_Song[10];
extern volatile uint8_t id_song;
extern volatile uint8_t flag_song;

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
    I2C_Init();
    ssd1306_t SSD1306;
    SSD1306.address = SSD1306_ADDR;
    SSD1306.width= SSD1306_WIDTH ;
    SSD1306.height = SSD1306_HEIGHT;
    SSD1306.color = SSD1306_WHITE;
    SSD1306.contrast = 0xCF;
    SSD1306.left = SSD1306_LEFT;
    SSD1306.right = SSD1306_RIGHT;
    SSD1306.center = SSD1306_CENTER;
    SSD1306_I2C_Init (&SSD1306);
    __delay_ms(100);
    
    SSD1306_I2C_SetFont( &SSD1306, SMALL_FONTS);
    SSD1306_I2C_Cadena( &SSD1306,0,0,cancion1);
    SSD1306_I2C_Cadena( &SSD1306, 0,16,cancion2);
    SSD1306_I2C_Cadena( &SSD1306,0,32,cancion3);
    SSD1306_I2C_Update( &SSD1306);
    __delay_ms(2000);
    
    __delay_ms(1000);
    DFPlayer_Config(&cmd_DFPlayer,DFP_SET_VOL,DFP_NONE,15);
    LATFbits.LATF2 = 1;
    UART_Tx('W');
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
        
        if(flag_song)
        {
            SSD1306_I2C_Cadena( &SSD1306,0,48,BT_Song);
            SSD1306_I2C_Update( &SSD1306);
            flag_song = 1;
        }
    }
    return 0;
}

