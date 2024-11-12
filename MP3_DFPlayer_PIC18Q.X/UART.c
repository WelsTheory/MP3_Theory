
#include "UART.h"


void UART_Init(void){
    // UART1
    U1CON0bits.BRGS = 0; // Formula 16
    U1BRG = 416; // 9600 Baudios
    
    U1CON0bits.MODE = 0; // Modo 8 bits UART
    U1CON1bits.ON = 1;   //Habilitar Puerto Serial
    
    U1CON0bits.TXEN = 1; // Tx Habilitado
    
    U1CON0bits.RXEN = 1; // Rx Habilitado
    
    RF0PPS = 0x20; // RF0 -> TX
    TRISFbits.TRISF1 = 1; // ENTRADA
    ANSELFbits.ANSELF1 = 0; // Digital
    WPUFbits.WPUF1 = 0; // habilitado pull up
    INLVLFbits.INLVLF1 = 0; // TTL
    SLRCONFbits.SLRF1 = 1; // Limitado
    ODCONFbits.ODCF1 = 0; // Push Pull 
    
    U1RXPPS = 0x29; // RF1 -> RX 
    //U1TXB = 'A'; //->> TSR
}

void UART_DFM_Init(void){
    // UART3
    U3CON0bits.BRGS = 0; // Formula 16
    U3BRG = 416; // 9600 Baudios
    
    U3CON0bits.MODE = 0; // Modo 8 bits UART
    U3CON1bits.ON = 1;   //Habilitar Puerto Serial
    
    U3CON0bits.TXEN = 1; // Tx Habilitado
    
    U3CON0bits.RXEN = 1; // Rx Habilitado
    
    RF5PPS = 0x26; // RF5 -> TX
    TRISFbits.TRISF4 = 1; // ENTRADA
    ANSELFbits.ANSELF4 = 0; // Digital
    WPUFbits.WPUF4 = 0; // habilitado pull up
    INLVLFbits.INLVLF4 = 0; // TTL
    SLRCONFbits.SLRF4 = 1; // Limitado
    ODCONFbits.ODCF4 = 0; // Push Pull 
    
    U3RXPPS = 0x2C; // RF4 -> RX 
}

void UART_BT_Init(void){
    // UART2
    U2CON0bits.BRGS = 0; // Formula 16
    U2BRG = 416; // 9600 Baudios
    
    U2CON0bits.MODE = 0; // Modo 8 bits UART
    U2CON1bits.ON = 1;   //Habilitar Puerto Serial
    
    U2CON0bits.TXEN = 1; // Tx Habilitado
    
    U2CON0bits.RXEN = 1; // Rx Habilitado
    
    RB7PPS = 0x23; // RB7 -> TX
    TRISBbits.TRISB6 = 1; // ENTRADA
    ANSELBbits.ANSELB6 = 0; // Digital
    WPUBbits.WPUB6 = 0; // habilitado pull up
    INLVLBbits.INLVLB6 = 0; // TTL
    SLRCONBbits.SLRB6 = 1; // Limitado
    ODCONBbits.ODCB6 = 0; // Push Pull 
    
    U2RXPPS = 0x0E; // RB6 -> RX 
}

//U1TXB = 'A'; ->> TSR
void UART_Tx(char dato){
    while(U1ERRIRbits.TXMTIF == 0); // SE est� enviando un dato
    //while(0 == PIR4bits.U1TXIF);
    //U3TXB -> uart1 uart 2 
    U1TXB = dato; // 
}

void DFM_Tx(char dato){
    while(U3ERRIRbits.TXMTIF == 0); // SE est� enviando un dato
    U3TXB = dato; // 
}

void putch(char txData){
    UART_Tx(txData);
}

char UART_Rx(void){
    return U1RXB; // 8 bits 
}

int getch(void)
{
    return UART_Rx();
}


#define START_Streaming 0x03
#define END_Streaming   0xFC