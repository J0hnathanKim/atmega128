#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int main(void)
{
    PORTB = 0xFF;      // 풀업 활성화
    DDRB = 0xFF;       // PORTB 출력 (LED)

    // INT0 설정
    EICRA |= (1 << ISC00) | (1 << ISC01);   // 상승 에지 감지 (0->1)
    EIMSK |= (1 << INT0);                   // INT0 인터럽트 활성화
    sei();                                  // 전역 인터럽트 허용

    while (1)
    {
        // 풀링 없이 루프는 비워도 됨
    }
}

// -----------------------------------------
// INT0 인터럽트 서비스 루틴
// -----------------------------------------
ISR(INT0_vect)
{
    // 버튼이 눌린 순간 LED 켜기
    PORTB ^= (1 << PB0);    // 토글 LED
    _delay_ms(50);
}
