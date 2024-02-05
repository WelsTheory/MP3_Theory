

#include "INT.h"
#include "UART.h"
#include "DFPlayer.h"

volatile uint8_t BT_RX[1] = {0};
volatile uint8_t BT_VOL[2] = {0};
volatile uint8_t id_vol = 0;
volatile int8_t volumen = 0;
volatile uint8_t flag_volumen = 0;
volatile uint8_t flag_DFP = 0;

void INT_Init(void){
     // INT0 
    TRISBbits.TRISB0 = 1; // ENTRADA
    ANSELBbits.ANSELB0 = 0; // Digital
    WPUBbits.WPUB0 = 1; // habilitado pull up
    INLVLBbits.INLVLB0 = 0; // TTL
    SLRCONBbits.SLRB0 = 1; // Limitado
    ODCONBbits.ODCB0 = 0; // Push Pull 
    
    PIE1bits.INT0IE = 1; // Habilitando INT0
    PIR1bits.INT0IF = 0; // Limpiar la alerta
    IPR1bits.INT0IP  = 0; // Habiliar Prioridad Baja
    
     // INT1 
    TRISBbits.TRISB1 = 1; // ENTRADA
    ANSELBbits.ANSELB1 = 0; // Digital
    WPUBbits.WPUB1 = 1; // habilitado pull up
    INLVLBbits.INLVLB1 = 0; // TTL
    SLRCONBbits.SLRB1 = 1; // Limitado
    ODCONBbits.ODCB1 = 0; // Push Pull 
    
    PIE6bits.INT1IE = 1; // Habilitando INT0
    PIR6bits.INT1IF = 0; // Limpiar la alerta
    IPR6bits.INT1IP  = 0; // Habiliar Prioridad Baja
    
    PIR4bits.U1RXIF = 0;
    PIE4bits.U1RXIE = 1;
    IPR4bits.U1RXIP = 1;
    
    /* BLUETOOTH */
//    PIR8bits.U2RXIF = 0;
//    PIE8bits.U2RXIE = 1;
//    IPR8bits.U2RXIP = 1;
    
    INTCON0bits.IPEN = 1; // Habilitar Prioridades
    INTCON0bits.GIEH = 1; // Habilitar INT Globales
    INTCON0bits.GIEL = 1; // Habilitar INT Prioridad Baja
    
    //IVTBASE = 200;
    //INTCON0bits.GIEH = 0;
    di();
    //di()
    IVTBASEU = 0x0;  //5 bits
    IVTBASEH = 0x02; //8 bits
    IVTBASEL = 0x00; //8 bits
    // 00200
    // IVTBASE = IVTBASEU + IVTBASEH + IVTBASEL
    ei();
    //INTCON0bits.GIEH = 1;
    
}

void __interrupt(irq(IRQ_INT0,IRQ_INT1), base(0x200), low_priority) InterrupcionINT0_isr(void)
{
    if(PIR1bits.INT0IF == 1)
    {
        volumen++;
        if(volumen >= 30)
        {
            volumen = 30;
        }
        PIR1bits.INT0IF = 0;
    }
    if(PIR6bits.INT1IF  == 1)
    {
        volumen--;
        if(volumen <= 0)
        {
            volumen = 0;
        }
        PIR6bits.INT1IF = 0;
    }
    flag_volumen = 1;
}

void __interrupt(irq(IRQ_U1RX), base(0x200), high_priority) Interrupcion_isr(void)
{
    if(PIR4bits.U1RXIF == 1)
    {
        if((UART_Rx() >= '0') && (UART_Rx() <= '9'))
        {
            BT_RX[0] = 'V';
            BT_VOL[id_vol] = UART_Rx();//10 09 25
            id_vol++;
            if(id_vol == 2)
            {
                id_vol = 0;
                flag_DFP = 1;
            }
        }
        else
        {
            BT_RX[0] = UART_Rx();
            flag_DFP = 1;
        }
        
        PIR4bits.U1RXIF = 0;
    }
}