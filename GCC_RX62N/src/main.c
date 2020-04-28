#include <stdint.h>
#include "iodefine.h"

#define LED1	PORTD.DR.BIT.B0
#define LED2	PORTD.DR.BIT.B1
#define LED3	PORTD.DR.BIT.B2
#define LED4	PORTD.DR.BIT.B3
#define LED5	PORTD.DR.BIT.B4
#define LED6	PORTD.DR.BIT.B5
#define LED7	PORTD.DR.BIT.B6
#define LED8	PORTD.DR.BIT.B7
#define LED9	PORTE.DR.BIT.B0
#define LED10	PORTE.DR.BIT.B1
#define LED11	PORTE.DR.BIT.B2
#define LED12	PORTE.DR.BIT.B3

#define	LED1_DDR	PORTD.DDR.BIT.B0
#define	LED2_DDR	PORTD.DDR.BIT.B1
#define LED3_DDR	PORTD.DDR.BIT.B2
#define LED4_DDR	PORTD.DDR.BIT.B3
#define LED5_DDR	PORTD.DDR.BIT.B4
#define LED6_DDR	PORTD.DDR.BIT.B5
#define LED7_DDR	PORTD.DDR.BIT.B6
#define LED8_DDR	PORTD.DDR.BIT.B7
#define LED9_DDR	PORTE.DDR.BIT.B0
#define LED10_DDR	PORTE.DDR.BIT.B1
#define LED11_DDR	PORTE.DDR.BIT.B2
#define LED12_DDR	PORTE.DDR.BIT.B3

volatile uint32_t test_u32;
volatile uint32_t i;
void main()
{
    LED12_DDR = 1;
    LED11_DDR = 1;
    LED12 = 0;
    LED11 = 0;
    while(1)
    {
        for(i = 0; i < 500000; i++)
        {
            test_u32++;
        }
        LED12 = 1;
        for(i = 0; i < 500000; i++)
        {
           test_u32++;
        }
        LED12 = 0;
    }
}
