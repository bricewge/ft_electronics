#include <xc.h>
#include <sys/attribs.h>

#define btn PORTDbits.RD8
#define led LATFbits.LATF1
#define q1 PORTCbits.RC12
#define q2 PORTCbits.RC15
#define freq 16000

int        ft_next_frq (int frq)
{
    if (frq == freq)
        return (freq / 2);
    else if (frq == freq / 2)
        return (freq / 4);
    else if (frq == freq / 4)
        return (freq / 8);
    else if (frq == freq / 8)
        return (freq / 16);
    else if (frq == freq / 16)
        return (freq);
}

int        ft_frq(int frq)
{
    static int event = 0;
    static int nop = 0;
    static int i_btn = 1;

    i_btn = btn;
    if (event && !i_btn && !nop)
    {
        frq = ft_next_frq(frq);
        nop = 1;
    }
    if (i_btn)
        nop = 0;
    event = !i_btn && !nop ? 1 : 0;
    return (frq);
}

int main(void) {
    int clk;
    int frq = freq;
    int state = 0;

    TRISFbits.TRISF1 = 0;

    clk = frq;
    while (1) {
        while (clk) {
            frq = ft_frq(frq);
            if (q1 || q2)
                clk--;
            state = 1;
        }
        led = state;
        while (clk < frq) {
            frq = ft_frq(frq);
            if (q1 || q2)
                clk++;
            state = 0;
        }
        led = state;
    }
}
