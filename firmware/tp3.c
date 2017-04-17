#include <xc.h>
#include <sys/attribs.h>
#include <proc/p32mx340f512h.h>

/*
void __ISR (_TIMER_2_VECTOR, IPL4SOFT) T2Interrupt(void)
{
    // Toggle LED LD1
    LATFINV = _LATF_LATF1_MASK;

    // Reset interrupt flag
    IFS0bits.T2IF = 0;
}

void __ISR (_EXTERNAL_1_VECTOR, IPL4SOFT) E1Interrupt(void)
{
    TMR2 = 0;
    if (PR2 <= 1220)
        PR2 = 19530;
    else
        PR2 /= 2;
    IFS0bits.INT1IF = 0;
}
*/
/*
int main3(void)
{
    TRISFbits.TRISF1 = 0; // LED
    TRISDbits.TRISD8 = 1; // Button

    // LED timer initialization
    T2CONbits.TON = 1;               
    T2CONbits.TCKPS = 7;           
    PR2 = 19530;                    
    TMR2 = 0;                      
    IPC2bits.T2IP = 4;               
    IFS0bits.T2IF = 0;          
    IEC0bits.T2IE = 1;               
    // Button timer initialization
    IPC1bits.INT1IP = 4;
    IFS0bits.INT1IF = 0;
    IEC0bits.INT1IE = 1;

    INTCONSET = _INTCON_MVEC_MASK;    
    __builtin_enable_interrupts();   

    //INTCONbits.INT1EP = 1;

    while(1)
    {
        WDTCONbits.WDTCLR = 1;
    }

}
*/
