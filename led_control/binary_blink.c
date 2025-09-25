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


int main(void)
{
	DDRF = 0xFF;
    int i;
	while (1) 
   {
	 for(i = 1; i <= 255; i++){
		 PORTF = 0xFF & i;
		_delay_ms(500);
	   }
    }
}

