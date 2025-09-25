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
	uint8_t LED = 0x01;
    while (1) 
    {
		PORTF = LED;
		_delay_ms(1000);
		LED = LED << 1;
		if(LED == 0) LED = 0x01;
    }
}

