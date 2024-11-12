
#include "I2C.h"

static void I2C_Gpio(void)
{
    /* RC3 */
    TRISCbits.TRISC3    = 0; // salida
    ANSELCbits.ANSELC3  = 0; // Digital
    WPUCbits.WPUC3      = 1; // habilitado 
    INLVLCbits.INLVLC3  = 0; // TTL
    SLRCONCbits.SLRC3   = 1; // limitado
    ODCONCbits.ODCC3    = 1; // Open Drain

    /* RC4 */
    TRISCbits.TRISC4    = 0; // salida
    ANSELCbits.ANSELC4  = 0; // Digital
    WPUCbits.WPUC4      = 1; // habilitado PULL UP
    INLVLCbits.INLVLC3  = 0; // TTL
    SLRCONCbits.SLRC3   = 1; // limitado
    ODCONCbits.ODCC3    = 1; // Open Drain
    
    RC3I2Cbits.PU = 2;
    RC3I2Cbits.TH = 1;
    RC4I2Cbits.PU = 2;
    RC4I2Cbits.TH = 1;
    // I2C1 INPUTS
    I2C1SCLPPS = 0b00010011;
    I2C1SDAPPS = 0b00010100;
    // I2C1 OUTPUTS
    RC3PPS = 0x37;
    RC4PPS = 0x38;
}

void I2C_Init(void)
{
    I2C_Gpio();
    // Deshabilitamos I2C
    I2C1CON0bits.EN = 0;
    // 500KHz CLOCK
    I2C1CLK = 0x03;
    I2C1CON2bits.FME = 0; // 500/5 = 100KHz
    I2C1CON2bits.SDAHT = 2;// 30nS Hold Time
    I2C1CON2bits.BFRET = 0; // 8 Pulsos
    I2C1CON2bits.ABD = 0;   // Registros de direccion
    I2C1CON0bits.MODE = 0b100; // Host 7 bits
    I2C1CNT = 0x00;
    I2C1CON0bits.EN = 1;    // Habilitado el I2C
}

/* 
 * DIRECCION
 * DATA
 * LONGITUD
 */
void I2C_SendBytes(uint8_t address, uint8_t* data, uint8_t len)
{
    uint8_t index = 1;
    I2C1CON0bits.EN = 1;
    I2C1ADB1 = (uint8_t)(address<<1);
    I2C1TXB = data[0];
    I2C1CNT = len;
    //START 
    I2C1CON0bits.S = 1;
    while(I2C1CON0bits.S);
    // HOST ACTIVE
    while(I2C1STAT0bits.MMA)
    {
        if(I2C1CON0bits.MDR)
        {
            if(I2C1STAT1bits.TXBE)
            {
                if(index >= len)
                {
                    I2C1TXB = 0x00;
                }
                else
                {
                   I2C1TXB = data[index];
                   index++; 
                }          
            }
        }
    }
}

/* 
 * DIRECCION
 * DATA
 * LONGITUD
 */
void I2C_ReadBytes(uint8_t address, uint8_t* data, uint8_t len)
{
    uint8_t index = 0;
    I2C1CON0bits.EN = 1;
    I2C1ADB1 = (uint8_t)(address<<1 | 0b1);
    I2C1CNT = len;
    //START 
    I2C1CON0bits.S = 1;
    while(I2C1CON0bits.S);
    // HOST ACTIVE
    while(I2C1STAT0bits.MMA)
    {
        if(I2C1STAT1bits.RXBF)
        {
            data[index] = I2C1RXB;
            index++;           
        }
    }
}