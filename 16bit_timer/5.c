#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define BUTTON PD4

volatile uint16_t captured_val = 0;
volatile uint8_t captured_flag = 0;
volatile uint16_t overflow_count = 0;

// Timer1 overflow interrupt
ISR(TIMER1_OVF_vect) {
    overflow_count++;
}

// Timer1 Input Capture interrupt
ISR(TIMER1_CAPT_vect) {
    captured_val = ICR1;      // 캡쳐값 저장
    captured_flag = 1;        // 메인 루프 알림
}

int main(void) {
    DDRA = 0xFF;     // LED 출력 (A0~A7)
    PORTA = 0x00;

    // 버튼 입력
    DDRD &= ~(1<<BUTTON);
    PORTD |= (1<<BUTTON);     // 풀업 사용

    // Timer1 설정
    TCCR1A = 0x00;            // Normal mode
    TCCR1B = (1<<ICES1);      // Input Capture rising edge
    TIMSK |= (1<<TICIE1)|(1<<TOIE1);   // ICP, Overflow 인터럽트 활성화
    sei();

    while(1) {
        // 타이머 초기화
        TCNT1 = 0;
        overflow_count = 0;
        captured_flag = 0;

        // 타이머 시작: prescaler 64 → 4us tick
        TCCR1B |= (1<<CS11)|(1<<CS10);

        // 버튼 누를 때까지 대기
        while(!captured_flag) {}

        // 타이머 정지
        TCCR1B &= ~((1<<CS12)|(1<<CS11)|(1<<CS10));

        // overflow 포함 시간 계산
        uint32_t ticks = (uint32_t)captured_val + ((uint32_t)overflow_count * 65536UL);
        uint32_t t_ms = ticks * 4 / 1000;   // tick = 4us → ms
        uint8_t seconds = t_ms / 1000;      // 초 단위
        if(seconds > 8) seconds = 8;        // 최대 8개 LED

        // LED 표시
        PORTA = (1 << seconds) - 1;         // 1초 → 00000001, 3초 → 00000111, 8초 → 11111111

        // 2초 정도 유지 후 초기화
        _delay_ms(2000);
        PORTA = 0x00;
    }
}
