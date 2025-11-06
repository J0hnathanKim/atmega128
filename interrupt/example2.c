/*
 * GccApplication21.c
 *
 * Created: 2025-11-06 오후 3:06:14
 * Author : Administrator
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int main(void)
{
	PORTD = 0xFF; //교재 내용과 다른 부분 수정
	DDRB = 0xFF;
	
	EICRA |= (1 << ISC00) | (1 << ISC01);
	EIMSK |= (1 << INT0);
	sei();
	
    /* Replace with your application code */
    while (1) 
    {
		
    }
}
ISR(INT0_vect){
	PORTB ^= (1 << PB0);
	_delay_ms(50);
}

