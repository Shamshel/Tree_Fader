/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

/* i.e. uint8_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

void main(void)
{
    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize I/O and Peripherals for application */
    InitApp();

    int red_duty_cycle = 255; //Duty cycle should be 0-255
    int red_cycle_count = 0;
    int red_direction = -1;

    PORTAbits.RA5 = 0;
    PORTAbits.RA4 = 0;
    PORTAbits.RA2 = 0;

    while(1)
    {
        //check RA0 for comparator output (1 is solar panel off)
        if(false)
        {
            PORTAbits.RA5 = 0;
            PORTAbits.RA4 = 0;
            PORTAbits.RA2 = 0;

        }

        else
        {
            //red timer -> TMR0
            if(TMR0 > red_duty_cycle)
            {
                PORTAbits.RA5 = 1;

            }

            if(INTCONbits.TMR0IF == 1)
            {
                INTCONbits.TMR0IF = 0;
                PORTAbits.RA5 = 0;

                red_cycle_count++;

                if(red_cycle_count == CYCLE_COUNT)
                {
                    red_cycle_count = 0;
                    red_duty_cycle += red_direction;

                    if(red_duty_cycle == 255)
                    {
                        red_direction = -1;

                    }

                    if(red_duty_cycle == 0)
                    {
                        red_direction = 1;

                    }

                }

            }

        }

    }

}

