#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char brightness = 0;   // LED 밝기
volatile unsigned char reverse = 0;      // 밝기 방향: 0=증가, 1=감소

// Timer0 Compare Match 인터럽트
ISR(TIMER0_COMP_vect){
	// LED 밝기 변화
	if(reverse){
		if(brightness > 0) brightness--;
		} else {
		if(brightness < 255) brightness++;
	}

	// 방향 전환
	if(brightness == 255) reverse = 1;
	else if(brightness == 0) reverse = 0;

	// OC0 핀에 PWM duty cycle 적용
	OCR0 = brightness;
}

int main(void){
	DDRB = 0xff; // OC0 핀 출력 (LED 연결)

	TCCR0 = (1<<WGM01) | (1<<WGM00) | (1<<COM01) | (0<<COM00) | (1<<CS02);

	OCR0 = 0;    // 초기 LED 밝기
	TIMSK |= (1<<OCIE0); // Timer0 Compare Match 인터럽트 활성화

	sei(); // 전역 인터럽트 활성화

	while(1){
	}
}
