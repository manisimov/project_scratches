#include <stdint.h>
#include <avr/io.h>
#include "main.h"

volatile uint16_t i;
void main()
{
    DDRB |= 1 << DDB0;
    PORTB |= 1 << PORTB0;
    while(1)
    {
        for(i = 0; i < 60000; i++)
        { /* Delay */
        }
        PORTB &= ~(1 << PORTB0);
        for(i = 0; i < 60000; i++)
        { /* Delay */
        }
        PORTB |= 1 << PORTB0;
    }
}
