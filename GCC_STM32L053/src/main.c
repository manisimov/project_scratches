#include <stdint.h>
#include "stm32l0xx.h"



volatile uint32_t test_u32;
void main()
{
    SystemInit();
    SystemCoreClockUpdate();
    RCC->IOPENR |= RCC_IOPENR_GPIOAEN;
    GPIOA->MODER &= ~GPIO_MODER_MODE5_Msk;
    GPIOA->MODER |= (0x01UL << GPIO_MODER_MODE5_Pos);
    GPIOA->ODR |= GPIO_ODR_OD5;
    

    while(1)
    {
        for(test_u32 = 0; test_u32 < 50000; test_u32++)
        { /* Delay */
        }
        GPIOA->ODR &= ~GPIO_ODR_OD5;
        for(test_u32 = 0; test_u32 < 50000; test_u32++)
        { /* Delay */
        }
        GPIOA->ODR |= GPIO_ODR_OD5;
    }
}
