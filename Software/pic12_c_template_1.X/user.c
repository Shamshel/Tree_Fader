/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#include "user.h"

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

void InitApp(void)
{
    /* TODO Initialize User Ports/Peripherals/Project here */

    /* Setup analog functionality and port direction */
    //disable analog operation
    ANSELA = 0;
    //setup RA5, RA4, and RA2 as output
    TRISAbits.TRISA2 = 0;
    TRISAbits.TRISA4 = 0;
    TRISAbits.TRISA5 = 0;

    //setup RA0 as input
    TRISAbits.TRISA0 = 1;

    /* Initialize peripherals */
    PORTAbits.RA2 = 0;
    PORTAbits.RA4 = 0;
    PORTAbits.RA5 = 0;

    //setup timers

    //setup timer 0
    TMR0 = 0;

    //set timer 0 source
    OPTION_REGbits.T0CS = 0;

    //set edge select bit
    OPTION_REGbits.T0SE = 0;

    //set prescaler to watchdog
    OPTION_REGbits.PSA = 1;

    //prescaler set to watchdog, PS2:0 have no effect
    /*
     * OPTION_REGbits.PS2 = 0;
     * OPTION_REGbits.PS1 = 0;
     * OPTION_REGbits.PS0 = 0;
     */

    /* Enable interrupts */
}

