#include <stdint.h>
#include "sam4s.h"
#include "system_sam4s.h"


volatile uint32_t test_u32;
void main()
{
    SystemCoreClockUpdate();

    while(1)
    {
        test_u32 = DWT->CTRL;
        test_u32 = 123;
    }
}
