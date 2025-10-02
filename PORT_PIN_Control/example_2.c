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
		PORTF = 0x00;
		// PC0~PC7 버튼 → PF0~PF7 LED
		if(PINC & 0x01) PORTF |= 0x01; // PC0 → PF0
		if(PINC & 0x02) PORTF |= 0x02; // PC1 → PF1
		if(PINC & 0x04) PORTF |= 0x04; // PC2 → PF2
		if(PINC & 0x08) PORTF |= 0x08; // PC3 → PF3
		if(PINC & 0x10) PORTF |= 0x10; // PC4 → PF4
		if(PINC & 0x20) PORTF |= 0x20; // PC5 → PF5
		if(PINC & 0x40) PORTF |= 0x40; // PC6 → PF6
		if(PINC & 0x80) PORTF |= 0x80; // PC7 → PF7
		
		_delay_ms(50);
	}
}
