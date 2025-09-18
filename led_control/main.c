/*
 * GccApplication1.c
 *
 * Created: 2025-09-18 오후 4:55:53
 * Author : Administrator
 */ 

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRF = 0xFF;
    /* Replace with your application code */
    while (1) 
    {
		PORTF = 0xFF;
		_delay_ms(1000);
		PORTF = 0x00;
		_delay_ms(1000);
    }
}

