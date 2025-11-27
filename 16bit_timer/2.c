#include <avr/io.h>
#include <avr/interrupt.h>

#define LED1 PB7   // 오버플로우 인터럽트 Led
#define LED2 PB6   // 비교 일치 인터럽트 a Led
#define LED3 PB5   // 비교 일치 인터럽트 b Led
#define LED4 PB4   // 비교 일치 인터럽트 c Led


ISR(TIMER1_COMPA_vect)
{
	PORTB ^= 1 << LED2;
}

ISR(TIMER1_COMPB_vect)
{
	PORTB ^= 1 << LED3;
}

ISR(TIMER1_COMPC_vect)
{
	PORTB ^= 1 << LED4;
}

ISR(TIMER1_OVF_vect)
{
	PORTB ^= 1 << LED1;
}

int main(void){
	DDRB = 0xff;
	
	OCR1A = 0x3fff;
	OCR1B = 0x7fff;
	OCR1C = 0xBFFF;
	
	TCCR1B |= (1 << CS12);
	TIMSK |= (1 << OCIE1A) | (1 << OCIE1B) | (1 << TOIE1);
	ETIMSK |= (1 << OCIE1C);
	
	sei();
	while(1){
		
	}
	return 0;
}
