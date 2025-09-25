/*
 * GccApplication1.c
 *
 * Created: 2025-09-18 오후 4:55:53
 * Author : Administrator
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
	DDRF = 0xFF;
    uint8_t led_pattern = 0x00;
	
	srand(1234);
    
	while (1) 
    {
		uint8_t rand_bit = 1 <<(rand() % 8);
		
		led_pattern ^= rand_bit;
		
		PORTF = led_pattern;
		_delay_ms(500);
    }
}

