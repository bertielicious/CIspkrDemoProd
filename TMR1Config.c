#include "config.h"
void TMR1Config(void)
{
    TMR1H = 0x00;
    TMR1L = 0x00;
    PIE1bits.TMR1IE = HIGH; //enable TMR1
    INTCONbits.PEIE = HIGH; // TMR1 interrupt enable bit
    T1CONbits.T1CKPS1 = HIGH; // 8 divisions of the clock input (0.5us)
    T1CONbits.T1CKPS0 = HIGH; // takes 262.14ms to overflow (0x0000 to 0xffff))
    T1CONbits.TMR1CS = LOW;     // internal clock fosc/8 = 2MHz/8 = 0.5us clock period
    INTCONbits.GIE = HIGH;      // global interrupts enabled
    T1CONbits.TMR1ON = LOW;    // TMR1 disabled
    PIR1bits.TMR1IF = LOW;      // clear TMR1 interrupt flag
}
