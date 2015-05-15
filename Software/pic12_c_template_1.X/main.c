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

    int cycle_count = 0;

    int red_duty_cycle = 255; //Duty cycle should be 0-255
    int red_direction = -1;

    int green_duty_cycle = 128; //Duty cycle should be 0-255
    int green_direction = -1;

    int blue_duty_cycle = 0; //Duty cycle should be 0-255
    int blue_direction = 1;

    PORTAbits.RA5 = 0;
    PORTAbits.RA4 = 0;
    PORTAbits.RA2 = 0;

    while(1)
    {
        //check RA0 for comparator output (1 is solar panel off)
        //charging (in sunlight)
        if(RA0 == 0)
        {
            PORTAbits.RA5 = 0;
            PORTAbits.RA4 = 0;
            PORTAbits.RA2 = 0;

            //switch to lower clock frequency to save power
            //50 uA/MHz @ 1.8V, typical -> 5e-8 A/kHz
            //set MF intosc, 125kHz (6e-6 A @ 1.8V)
            if(OSCCON != 0b01000000)
            {
                OSCCON = 0b01000000;

                //wait for MF startup and stable
                while(OSCSTATbits.MFIOFR != 1);

            }

        }

        //discharging (out of sunlight)
        else
        {
            //switch to higher frequency to eliminate (minimize) fliker
            if(OSCCON != 0b01011010)
            {
                OSCCON = 0b01011010;

                while(OSCSTATbits.HFIOFR != 1);

            }

            //red timer -> TMR0
            if(TMR0 > red_duty_cycle)
            {
                PORTAbits.RA2 = 1;

            }

            if(TMR0 > green_duty_cycle)
            {
                PORTAbits.RA5 = 1;

            }

            if(TMR0 > blue_duty_cycle)
            {
                PORTAbits.RA4 = 1;

            }

            if(INTCONbits.TMR0IF == 1)
            {
                INTCONbits.TMR0IF = 0;

                PORTAbits.RA5 = 0;
                PORTAbits.RA4 = 0;
                PORTAbits.RA2 = 0;

                cycle_count++;

                if(cycle_count == CYCLE_COUNT)
                {
                    cycle_count = 0;
                    red_duty_cycle += red_direction;
                    green_duty_cycle += green_direction;
                    blue_duty_cycle += blue_direction;


                    if(red_duty_cycle == 255)
                    {
                        red_direction = -1;

                    }

                    if(red_duty_cycle == 0)
                    {
                        red_direction = 1;

                    }

                    if(green_duty_cycle == 255)
                    {
                        green_direction = -1;

                    }

                    if(green_duty_cycle == 0)
                    {
                        green_direction = 1;

                    }

                    if(blue_duty_cycle == 255)
                    {
                        blue_direction = -1;

                    }

                    if(blue_duty_cycle == 0)
                    {
                        blue_direction = 1;

                    }

                }

            }

        }

    }

}

