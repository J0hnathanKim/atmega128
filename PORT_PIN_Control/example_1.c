/*
 * GccApplication5.c
 *
 * Created: 2025-09-29 오후 3:00:49
 * Author : Administrator
 */ 
#define F_cpu 16000000UL
#include <avr/io.h>
#include <util/delay.h>



int main(void)
{
	DDRF = 0xFF;
	DDRC = 0x00;
	
	while (1)
	{
		if((PINC & 0x01) == 0x01)
		PORTF = 0xFF;
		else
		PORTF = 0x00;
		_delay_ms(500);
	}
}
