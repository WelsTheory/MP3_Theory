
#ifndef UART_H
#define	UART_H

#include <xc.h> // include processor files - each processor file is guarded.  

void UART_Init(void);

void UART_DFM_Init(void);

void UART_BT_Init(void);

//U1TXB = 'A'; ->> TSR
void UART_Tx(char dato);

void DFM_Tx(char dato);

void putch(char txData);

char UART_Rx(void);

char getch(void);


#define START_Streaming 0x03
#define END_Streaming   0xFC

#endif	/* XC_HEADER_TEMPLATE_H */

