#include <stdint.h>

#define GPFSEL1 (*((uint32_t*)0x20200004))
#define GPSET0  (*((uint32_t*)0x2020001C))
#define GPCLR0  (*((uint32_t*)0x20200028))

volatile uint32_t test_u32;

int main (void)
{
    GPFSEL1 &= ~(7 << 18);
    GPFSEL1 |= 1 << 18;
    while(1)
    {
        GPSET0 = 1 << 16;
        for(int i = 0; i < 0x150000; i++)
        {
            test_u32++;
        }
        GPCLR0 = 1 << 16;
        for(int i = 0; i < 0x150000; i++)
        {
            test_u32++;
        }
    }
    
    return 0;
}

