#include <xc.h>

int main(void)
{
    int prev = 0;
    int but;
    int times = 1;
    int cnt = 0;

    TRISFbits.TRISF1 = 0;
    TRISDbits.TRISD8 = 1;
    while (1)
    {
        but = PORTDbits.RD8;
        if (but == 0 && but != prev)
        {
            if (times == 5)
                times = 1;
            else
                ++times;
        }
        cnt = 0;
        while (cnt != 16000 / times)
        {
            ++cnt;
        }
        if (LATFbits.LATF1 == 1)
            LATFbits.LATF1 = 0;
        else
            LATFbits.LATF1 = 1;
        prev = but;
    }
}
