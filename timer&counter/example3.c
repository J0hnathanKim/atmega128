#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile unsigned char count = 1;
volatile unsigned int msec = 0;

// 7-세그먼트 데이터
char ss_data[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0x7f, 0x67};

// 디스플레이 제어 함수
void display_number(unsigned int number) {
    PORTC = 0x0F; // 모든 Digit 비활성화 (HIGH로 설정)

    // 천의 자리
    PORTA = ss_data[number / 1000];
    PORTC = 0x0e; // 3번 Digit 선택 (LOW로 활성화)
    _delay_ms(1); // 짧은 대기

    // 백의 자리
    PORTA = ss_data[(number % 1000) / 100];
    PORTC = 0x0d; // 2번 Digit 선택
    _delay_ms(1);

    PORTA = 0x80; // dot point 출력
    PORTC = 0x0d; // 2번 Digit 선택
    _delay_ms(1);

    // 십의 자리
    PORTA = ss_data[(number % 100) / 10];
    PORTC = 0x0b; // 1번 Digit 선택
    _delay_ms(1);

    // 일의 자리
    PORTA = ss_data[number % 10];
    PORTC = 0x07; // 0번 Digit 선택
    _delay_ms(1);
}

// 타이머 0 출력 비교 매치 인터럽트
ISR(TIMER0_COMP_vect) {
    count--;
    if (count == 0) {
        msec++;
        if (msec >= 6000) msec = 0;
        count = 10; // 다음 인터럽트 주기 설정
    }
}

int main(void) {
    DDRA = 0xFF; // PORTA 출력 (7-세그먼트 데이터)
    DDRC = 0x0F; // PORTC 하위 4비트 출력 (Digit 선택)
    PORTA = 0x00; // 초기화
    PORTC = 0x0F; // 모든 Digit 비활성화

    // 타이머 0 설정
    TCCR0 = (1 << WGM01) | (1 << CS02); // CTC 모드, 분주비 64
    OCR0 = 249; // 1ms 주기
    TIMSK |= (1 << OCIE0); // 타이머 비교 매치 인터럽트 활성화

    sei(); // 전역 인터럽트 활성화

    while (1) {
        display_number(msec); // 현재 시간 표시
    }
}
