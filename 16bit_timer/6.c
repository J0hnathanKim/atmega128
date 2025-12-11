#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile uint16_t t1 = 0;
volatile uint16_t t2 = 0;
volatile uint8_t state = 0;

volatile uint16_t overflow_count = 0;
volatile uint32_t measured_ms = 0;    // 측정된 시간 저장

char ss_data[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0x7f, 0x67};

void display_number(uint32_t number)
{
    PORTC = 0x0f;

    PORTA = ss_data[number / 1000];
    PORTC = 0x0e;
    _delay_ms(1);

    PORTA = ss_data[(number % 1000) / 100];
    PORTC = 0x0d;
    _delay_ms(1);

    PORTA = ss_data[(number % 100) / 10];
    PORTC = 0x0b;     // dot on
    _delay_ms(1);

    PORTA = ss_data[number % 10];
    PORTC = 0x07;
    _delay_ms(1);
}

// Timer1 overflow
ISR(TIMER1_OVF_vect)
{
    overflow_count++;
}

ISR(TIMER1_CAPT_vect)
{
    uint16_t now = ICR1;

    if (state == 0 || state == 3)
    {
        // 첫 펄스 상승
        t1 = now;
        overflow_count = 0;
        state = 1;   // 다음 펄스 기다림
        return;
    }

    if (state == 1)
    {
        // 두 번째 펄스
        t2 = now;
        state = 2;
        return;
    }
}

int main(void)
{
    DDRA = 0xff;
    DDRC = 0xff;

    DDRD &= ~(1 << PD4);
    TCCR1B |= (1 << CS11) | (1 << CS10);
    TCCR1B |= (1 << ICES1);
    TIMSK |= (1 << TICIE1) | (1 << TOIE1);

    sei();

    while (1)
    {
        // 두 펄스 측정 기록 & 계산
        if (state == 2)
        {
            uint32_t diff = t2 + ((uint32_t)overflow_count * 65536UL) - t1;
            uint32_t ms = diff * 4 / 1000;

            if (ms < 20)
            {
                state = 0;
                continue;
            }

            measured_ms = ms / 10;
            state = 3;     // 측정 완료 → 표시 모드
        }

        display_number(measured_ms);
    }
}
