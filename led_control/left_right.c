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
	uint8_t a = 0x01;
	int8_t dir = 1;
    while (1) 
    {
		PORTF = a;
		_delay_ms(1000);
		
		if(dir == 1)
		a = a << 1;
		else
		a = a >> 1;
		
		if(a == 0x80)
		dir = -1;
		else if(a == 0x01)
		dir = 1;
    }
}

