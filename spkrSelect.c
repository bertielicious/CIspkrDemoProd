#include "config.h"
#include "stdio.h"
#include "byteToBin.h"
#include "clearLCD.h"
void spkrSelect(uchar *currentEvent, uchar *prevEvent, uchar *numSpkrz)
{
    const uchar rotate[]={"rotate"};
    const uchar press[]={"press"};
    const uchar rotateOrPress[]={"rotate or press"};
    const uchar numb[]={"number of pairs "};
    const uchar numb2[]={"of demo spkrs?"};
    const uchar select1[]={"sel spkr to play"};
    const uchar playspksA[]={"play speakers A? "};
    const uchar rotateSpkrs[]={"rotate speakers "};
    const uchar muted[]={"speakers muted "};
    const uchar activeA[]={"spkrs A playing "};
    const uchar playspksB[]={"play speakers B? "};
    const uchar activeB[]={"spkrs B playing "};
    const uchar playspksC[]={"play speakers C? "};
    const uchar activeC[]={"spkrs C playing "};
    uchar *ptrNumb;
    
    switch(*currentEvent)
    {
        case 1:
            ptrNumb = &numb[0];
            byteToBin(LOW, 0x80);
            while(*ptrNumb > 0)
            {
                byteToBin(HIGH, *ptrNumb);  // write "numb of pairs" on LCD top line
                ptrNumb++;
            }
            ptrNumb = &numb2[0];
            byteToBin(LOW, 0xc0);
            while(*ptrNumb > 0)
            {
                byteToBin(HIGH, *ptrNumb);// write "of demo spkrs" on LCD bottom line
                ptrNumb++;
            }
            
            byteToBin(LOW,0xcf);
            byteToBin(HIGH,((count%3)+1)+0x30); // 
            if(SW==HIGH)
            {
                *currentEvent = 1;      //transition Z
            }
            if(SW==LOW)
            {
                *currentEvent = 2;      //transition A
                *prevEvent = 1;
            }
            break;
        case 2:
            while(SW==LOW);         // wait for button release
            *numSpkrz = (count%3)+1;
            stop = *numSpkrz;
            CWflag = LOW;
            
            *currentEvent = 3;      //transition B
            *prevEvent = 2;
            clearLCD();
            break;
        case 3:
            ptrNumb = &select1[0];
            byteToBin(LOW, 0x80);
            while(*ptrNumb > 0)
            {
                byteToBin(HIGH, *ptrNumb);  // write "select spkrs to play" on LCD top line
                ptrNumb++;
            }
             if(CWflag==HIGH && stop>1)
            {
                *currentEvent = 10;
                CWflag = LOW;
            }
             if(SW==LOW && *prevEvent==2 && *numSpkrz > 0) // transition C
             {
                 while(SW==LOW);
                 *currentEvent = 4;
                 *prevEvent = 3;
             }
            break;
        case 4:
            ptrNumb = &playspksA[0];
            byteToBin(LOW, 0x80);
            while(*ptrNumb > 0)
            {
                byteToBin(HIGH, *ptrNumb);  // write "play spkrs A?" on LCD top line
                ptrNumb++;
            }
            if(CWflag == HIGH && *numSpkrz > 1)
            {
                *currentEvent = 6;
                CWflag = 0;
            }
            
    
            if(SW==LOW && *prevEvent==3)   // transition E
            {
                while(SW==LOW);
                *currentEvent = 5;
                *prevEvent = 4;   
            }
            
            else if(SW==LOW && *prevEvent==5)// transition D
            {
                while(SW==LOW);
                *currentEvent = 3;
                *prevEvent = 2; 
            }
            break;
        case 5:
            ptrNumb = &activeA[0];
            byteToBin(LOW, 0x80);
            while(*ptrNumb > 0)
            {
                byteToBin(HIGH, *ptrNumb);  // write "spkrs A playing" on LCD top line
                ptrNumb++;
            }
            RL1 = HIGH;
            if(SW==LOW && *prevEvent == 4)
            {
                while(SW==LOW);
                *currentEvent = 4;
                *prevEvent = 5;
                 RL1 = LOW;
            }
            break;
        case 6:
            RL1=LOW;
            RL2=LOW;
            RL3=LOW;
            ptrNumb = &playspksB[0];
            byteToBin(LOW, 0x80);
            while(*ptrNumb > 0)
            {
                byteToBin(HIGH, *ptrNumb);  // write "play spkrs A?" on LCD top line
                ptrNumb++;
            }
            
            if(ACWflag==HIGH)
            {
                 *currentEvent = 4;
                 ACWflag = LOW;
            }
            if(CWflag==HIGH && *numSpkrz > 2)
            {
                *currentEvent = 8;      // transition P
                CWflag = LOW;
            }
            if(SW==LOW)
            {
                while(SW==LOW);
                *currentEvent = 7;
            }
            break;
        case 7:
            ptrNumb = &activeB[0];
            byteToBin(LOW, 0x80);
            while(*ptrNumb > 0)
            {
                byteToBin(HIGH, *ptrNumb);  // write "spkrs A playing" on LCD top line
                ptrNumb++;
            }
            RL2 = HIGH;
            if(SW==LOW)
            {
                while(SW==LOW);
                *currentEvent = 6;
                RL2 = LOW;
            }
            break;
        case 8:
            RL1=LOW;
            RL2=LOW;
            RL3=LOW;
            ptrNumb = &playspksC[0];
            byteToBin(LOW, 0x80);
            while(*ptrNumb > 0)
            {
                byteToBin(HIGH, *ptrNumb);  // write "play spkrs A?" on LCD top line
                ptrNumb++;
            }
            if(ACWflag==HIGH)
            {
                *currentEvent = 6;
                ACWflag = LOW;
            }
            if(SW==LOW)
            {
                while(SW==LOW);
                *currentEvent = 9;
            }
            break;
        case 9:
            ptrNumb = &activeC[0];
            byteToBin(LOW, 0x80);
            while(*ptrNumb > 0)
            {
                byteToBin(HIGH, *ptrNumb);  // write "spkrs A playing" on LCD top line
                ptrNumb++;
            }
            RL3 = HIGH;
            if(SW==LOW)
            {
                while(SW==LOW);
                *currentEvent = 8;      // transition S
                RL2 = LOW;
            }
            break;
        case 10:
            T1CONbits.TMR1ON = HIGH;    // TMR1 enabled
            CWflag = LOW;
            ACWflag = LOW;
            ptrNumb = &rotateSpkrs[0];
            byteToBin(LOW, 0x80);
            while(*ptrNumb > 0)
            {
                byteToBin(HIGH, *ptrNumb);  // write "rotate spkrs" on LCD top line
                ptrNumb++;
            }
            if(sFlag == 0)
            {
            ptrNumb = &activeA[0];
            byteToBin(LOW, 0xc0);
            while(*ptrNumb > 0)
                {
                    byteToBin(HIGH, *ptrNumb);  // write "spkrs A playing" on LCD top line
                    ptrNumb++;
                }
            }
            else if(sFlag == 1)
            {
            ptrNumb = &activeB[0];
            byteToBin(LOW, 0xc0);
            while(*ptrNumb > 0)
                {
                    byteToBin(HIGH, *ptrNumb);  // write "spkrs A playing" on LCD top line
                    ptrNumb++;
                }
            }
            else if(sFlag == 2 && stop > 2)
            {
            ptrNumb = &activeC[0];
            byteToBin(LOW, 0xc0);
            while(*ptrNumb > 0)
                {
                    byteToBin(HIGH, *ptrNumb);  // write "spkrs A playing" on LCD top line
                    ptrNumb++;
                }
            }
                
            if(ACWflag==HIGH)
            {
                clearLCD();
                *currentEvent = 3;
                ACWflag = LOW;
                T1CONbits.TMR1ON = LOW;    // TMR1 disabled
                RL1=LOW;
                RL2=LOW;
                RL3=LOW;
                sFlag = 0;
                overflows = 0;
            }
            
            
            break;
    }
    //printf("CE %d\t PE %d\t NUMSPKRZ %d CWflag %d\n", *currentEvent, *prevEvent, *numSpkrz, CWflag);
    printf("stop %d\toverflows %d\t   sFlag %d\n", stop, overflows, sFlag);
}