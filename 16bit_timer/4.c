#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile uint16_t t_rise = 0;
volatile uint16_t t_fall = 0;
volatile uint8_t state = 0;

volatile uint16_t overflow_count = 0; // Timer overflow 횟수 저장

void blink(uint8_t count) {
    for (uint8_t i = 0; i < count; i++) {
        PORTA |= (1 << PA0);
        _delay_ms(150);
        PORTA &= ~(1 << PA0);
        _delay_ms(150);
    }
}

// Timer1 overflow interrupt
ISR(TIMER1_OVF_vect) {              // 오버플로우 횟수 증가
    overflow_count++;
}

ISR(TIMER1_CAPT_vect) {
    uint16_t now = ICR1;

    if (state == 0) {               // Rising edge
        t_rise = now;
        overflow_count = 0;         // 펄스 시작에서 overflow count 리셋
        TCCR1B &= ~(1 << ICES1);
        state = 1;
    } else {                        // Falling edge
        t_fall = now;
        TCCR1B |= (1 << ICES1);
        state = 2;
    }
}

int main(void) {
    // LED 출력
    DDRA |= (1 << PA0);

    // 버튼 입력 (ICP1 = PD4)
    DDRD &= ~(1 << PD4);

    // Timer1 prescaler = 64
    TCCR1B |= (1 << CS11) | (1 << CS10);

    // Rising edge에서 캡쳐 시작
    TCCR1B |= (1 << ICES1);

    // 인터럽트 enable
    TIMSK |= (1 << TICIE1) | (1 << TOIE1); // overflow interrupt 추가

    sei();

    while (1) {
        if (state == 2) {
            // overflow 포함 시간 계산
            uint32_t diff = t_fall + ((uint32_t)overflow_count * 65536UL) - t_rise;

            // tick = 4us
            uint32_t ms = diff * 4 / 1000; // ms 변환

            // 디버그 출력
            if (ms < 20) {
                state = 0;
                continue;
            }

            // LED 출력
            if (ms < 2000)     blink(1); // 짧게
            else if (ms < 4000) blink(2); // 중간
            else               blink(3); // 길게

            state = 0;
        }
    }
}
