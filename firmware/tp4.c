#include <xc.h>
#include <sys/attribs.h>
#include <proc/p32mx340f512h.h>

int ttotal = 195;

void __ISR (_TIMER_2_VECTOR, IPL4SOFT) T2Interrupt(void)
{
    static int flag = 0;
    static int thigh = 146;
    static int up = 0;
    TMR2 = 0;
    // Toggle LED LD1
    if (flag == 0)
    {
        flag = 1;
        LATFbits.LATF1 = 1;
        PR2 = thigh;
    }
    else
    {
        flag = 0;
        LATFbits.LATF1 = 0;
        PR2 = ttotal - thigh;
    }
    if (up == 0)
        thigh--;
    else if (up == 1)
        thigh++;
    if (thigh == ttotal)
        up = 0;
    else if (thigh == 0)
        up = 1;

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

int main4(void)
{
    TRISFbits.TRISF1 = 0; // LED
    TRISDbits.TRISD8 = 1; // Button

    // LED timer initialization
    T2CONbits.TON = 1;                /* turn off Timer 2 */
    T2CONbits.TCKPS = 7;                /* pre-scale = 1:256 (T2CLKIN = 39062.5 Hz) */
    PR2 = 1953;                    /* T2 period ~ 100mS */
    TMR2 = 0;                        /* clear Timer 2 counter */
    IPC2bits.T2IP = 4;                /* Set Timer 2 interrupt priority to 7 */
    IFS0bits.T2IF = 0;                /* Reset the Timer 2 interrupt flag */
    IEC0bits.T2IE = 1;                /* Enable interrupts from Timer 2 */
    // Button timer initialization
    IPC1bits.INT1IP = 4;
    IFS0bits.INT1IF = 0;
    IEC0bits.INT1IE = 1;

    INTCONSET = _INTCON_MVEC_MASK;    /* Set the interrupt controller for multi-vector mode */
    __builtin_enable_interrupts();    /* Set the CP0 Status IE bit to turn on interrupts globally */

    while(1)
    {
        WDTCONbits.WDTCLR = 1;
    }

}