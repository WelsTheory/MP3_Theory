 
#ifndef CONFIGURACION_H
#define	CONFIGURACION_H

#include <xc.h> // include processor files - each processor file is guarded.  

#define _XTAL_FREQ  64000000UL

void Clock_Init(void);

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

