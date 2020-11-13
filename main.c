#include <msp430g2553.h>


/**
 * main.c
 */
void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    P1DIR = BIT0;//Sets switch to input and LED1 to output
    P1OUT = 0;//Sets LED1 to low
    /*
        P1IN register cannot be assigned a value
        the P1IN register holds the current state of ech pin in port 1
        the states can be 0(low) or 1(high)
        therefore remove P1IN |= 0x08;//Sets switch to high
    */
    // P1IN |= 0x08;//Sets switch to high

    /*
        in order to check if the button connected to P1.3 is pressed you have to
        connect a pull up/down resistor to the button. There is an internal
        resistor which can be used as a pull up/down resistor.
        E.g.
        P1REN = 0x04;   // this is used to enable the pull up/down resistor
        P1OUT |= 0x04;  // this will make the BIT 3 high which means we are
                        // selecting a pull up resistor

        check page 328 & 329 look at section 8.2.4 first then 8.2.2
    */

    P1REN = BIT3;
    P1OUT |= BIT3;

    while(1)
    {
        /*
            if you want to check if the button connected to P1.3 is pressed you
            want to do a bitwise & with the register P1IN and BIT3
        */
        if((P1IN & BIT3) != BIT3)   //if switch input becomes low then toggle LED1
        {
            P1OUT ^= 0x01;
            volatile int i;
            for(i = 0; i < 20000; i++);
        }
    }

}
