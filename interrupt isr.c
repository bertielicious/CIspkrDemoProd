#include "config.h"
#include "encDebounce.h"
#include "byteToBin.h"
#include "nibToBin.h"
#include "scrollLCD.h"

void interrupt isr(void)
{
    if(INTCONbits.T0IF == HIGH)
    {
        encDebounce();
        TMR0 = 0xf0;
        INTCONbits.T0IF = LOW;    
    }
    
    
   if(PIR1bits.TMR1IF == HIGH)
    {
       if(stop == 2 && sFlag == 0)    // spkrs A & B available to play
       {
           RL1 = HIGH;                  // spkrs A playing
           RL2 = LOW;
           RL3 = LOW;
           if(overflows >113)
            {
                sFlag = 1;
                overflows = 0;
            }
       }
       else if(stop == 2 && sFlag == 1)
       {
           RL1 = LOW;                  // spkrs B playing
           RL2 = HIGH;
           RL3 = LOW;
           if(overflows >113)
            {
                sFlag = 0;
                overflows = 0;
            }
           
       }
       if(stop == 3 && sFlag == 0)    // spkrs A & B available to play
       {
           RL1 = HIGH;                  // spkrs A playing
           RL2 = LOW;
           RL3 = LOW;
           if(overflows >113)
            {
                sFlag = 1;
                overflows = 0;
            }
       }
       else if(stop == 3 && sFlag == 1)
       {
           RL1 = LOW;                  // spkrs B playing
           RL2 = HIGH;
           RL3 = LOW;
           if(overflows >113)
            {
                sFlag = 2;
                overflows = 0;
            }   
       }
       else if(stop == 3 && sFlag == 2)
       {
           RL1 = LOW;                  // spkrs B playing
           RL2 = LOW;
           RL3 = HIGH;
           if(overflows >113)
            {
                sFlag = 0;
                overflows = 0;
            }   
       }
       
          
        
       
    TMR1H = 0x00;
    TMR1L = 0x00;
    PIR1bits.TMR1IF = LOW;
    overflows++;
    
    }
     
    
}
 