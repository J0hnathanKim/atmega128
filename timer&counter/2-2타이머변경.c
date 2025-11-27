//Timer0 -> Timer2로 바꾼코드
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char brightness = 0; // LED 밝기
volatile unsigned char reverse = 0;    // 밝기 방향: 0 - 증가, 1 - 감소

// Timer2 Compare Match 인터럽트
ISR(TIMER2_COMP_vect){
    // LED 밝기 변화
    if(reverse){
        if(brightness > 0) brightness--;
    } else {
        if(brightness < 255) brightness++;
    }

    // 방향 전환
    if(brightness == 255) reverse = 1;
    else if(brightness == 0) reverse = 0;

    OCR2 = brightness;   // PWM duty 적용
}

int main(void){
    DDRD |= (1<<PD7);  // PD7 = OC2 (LED 출력 핀)

    // Timer2 Fast PWM 설정
    TCCR2 = (1<<WGM21) | (1<<WGM20) | (1<<COM21) | (1<<CS22); 
    // Fast PWM + 비반전 모드 + 분주 64

    OCR2 = 0; // 초기 밝기

    TIMSK |= (1<<OCIE2); // Timer2 Compare Match interrupt enable

    sei(); // 전역 인터럽트 활성화

    while(1){
        // 메인 루프
    }
}
