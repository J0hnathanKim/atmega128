#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define MOVE_DELAY 100   // LED 이동 딜레이 (밀리초 단위)

volatile int position = 0x01;      // 초기 LED 포지션 (1번 핀)
volatile short direction = 0;      // 초기 방향 (좌측 이동)
volatile uint8_t stop_flag = 1;    // LED 이동 상태 (1: 정지, 0: 이동)

void setup() {

	DDRB = 0xFF;                   
	EICRA = 0x0F;                  // INT0, INT1: 상승 에지에서 인터럽트 트리거
	EIMSK = 0x03;                  // INT0, INT1 인터럽트 활성화
	sei();                         // 전역 인터럽트 활성화
}

int main(void) {
	setup();
	PORTB = position;              // 초기 LED 상태 출력

	while (1) {
		if (stop_flag == 0) {      // 이동 상태일 때만 실행
			switch (direction) {
				case 0:             // 좌측 이동
				if (position == 0x80)
				direction = 1;  // 끝에 도달 시 우측 이동으로 변경
				else
				position <<= 1; // LED 한 칸 좌측 이동
				break;

				case 1:             // 우측 이동
				if (position == 0x01)
				direction = 0;  // 시작점 도달 시 좌측 이동으로 변경
				else
				position >>= 1; // LED 한 칸 우측 이동
				break;
			}
		}

		PORTF = position;          // LED 상태 업데이트
		_delay_ms(MOVE_DELAY);     // 이동 속도
	}
}

// INT0 인터럽트: LED 이동 시작/정지
ISR(INT0_vect) {
	_delay_ms(50);                 // 디바운싱
	stop_flag = !stop_flag;        // LED 이동 상태 토글
}

// INT1 인터럽트: 방향 변경
ISR(INT1_vect) {
	_delay_ms(50);                 // 디바운싱
	direction = !direction;        // 방향 토글 (0 -> 1, 1 -> 0)
}
