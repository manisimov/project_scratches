#include <stdint.h>
#include "stm32l0xx.h"



volatile uint32_t test_u32;
void main()
{
    SystemInit();
    SystemCoreClockUpdate();

    while(1)
    {
        test_u32 = SCB->CPUID;
        test_u32 = 123;
    }
}
