#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

#define LED1 PB7     // 8bit 타이머 카운터 사용할 led
#define LED2 PB6     // 16bit 타이머 카운터 사용할 led

volatile unsigned long timer0;      // 오버플로우마다 1씩 증가될 변수

ISR(TIMER0_OVF_vect)
{
    timer0++;
    if(timer0 % 1000 == 0){         // 오버플로마다 1씩 증가
        PORTB ^= 1 << LED1;         // PORTB의 LED 위치 비트를 반전시킴
    }
}

ISR(TIMER1_OVF_vect)
{
    PORTB ^= 1 << LED2;             // PORTB의 LED 위치 비트를 반전시킴
}

int main(void)
{
    DDRB |= (1 << LED1);
    DDRB |= (1 << LED2);            // LED 출력 핀으로 설정

    TCCR0B |= (1 << CS02) | (1 << CS01);     // 256 분주 프리스케일러
    TCCR1B |= (1 << CS12) | (1 << CS10);     // 1024 분주 프리스케일러

    TIMSK |= (1 << TOIE0);
    TIMSK |= (1 << TOIE1);          // 타이머/카운터 인터럽트 활성화

    sei();

    while(1){
    }

    return 0;
}
