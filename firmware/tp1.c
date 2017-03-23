#include <xc.h>

int main(void)
{
    int prev = 0;
    int but;

    TRISFbits.TRISF1 = 0;
    TRISDbits.TRISD8 = 1;
    while (1)
    {
        but = PORTDbits.RD8;
        if (but == 0 && but != prev && LATFbits.LATF1 == 1)
            LATFbits.LATF1 = 0;
        else if (but == 0 && but != prev && LATFbits.LATF1 == 0)
            LATFbits.LATF1 = 1;
        prev = but;
    }
}
