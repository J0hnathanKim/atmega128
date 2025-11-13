#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>

volatile int cnt;

ISR(TIMER0_OVF_vect){
	cnt++;
	TCNT0 = 131;
	if(cnt == 500){
		PORTA = ~PORTA;
		cnt = 0;
	}
}

int main(void)
{
	DDRA = 0xff;
	PORTA = 0xaa;

	TCCR0 = (0<<WGM01) | (0<<WGM00) | (0<<COM01) | (0<<COM00) | (1<<CS02) | (1<<CS01) | (0<<CS00);
	TIMSK = 1<<TOIE0;
	sei();

	while(1)
	{
	}
}
