  
#ifndef inte_h
#define	inte_h

#include <xc.h> // include processor files - each processor file is guarded.  

void INT_Init(void);

void __interrupt(irq(IRQ_INT0), base(0x200), low_priority) Interrupcion_isr(void);

void __interrupt(irq(IRQ_U1RX), base(0x200), high_priority) Interrupcion_isr(void);

#endif	/* XC_HEADER_TEMPLATE_H */

