//3번버튼 -> 0으로 초기화
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
// 초기값: 0000 / 카운트업 할 시: 0001 0002 0003 .... 0009 1110 / 카운트다운: 9991 9990 88889....
// 7-Segment 출력 데이터 (0~9)
char ss_data[10] = {
	0x3F, // 0
	0x06, // 1
	0x5B, // 2
	0x4F, // 3
	0x66, // 4
	0x6D, // 5
	0x7D, // 6
	0x07, // 7
	0x7F, // 8
	0x6F  // 9
};

// 장치 초기화 함수
void init_devices(void) {
	DDRA = 0xFF;  // PORTA: 출력 (7-Segment 데이터)
	DDRC = 0xFF;  // PORTC: 하위 4비트 출력 (Digit 선택)
	DDRD = 0x00;  // PORTD: 입력 (버튼 입력)
}

// 2자리 숫자 표시 (멀티플렉싱)
void display_number(unsigned int number) {
	PORTC = 0x0F;  // 모든 Digit 비활성화
	PORTA = ss_data[number % 10];  // 일의 자리 표시
	PORTC = 0x07; // Digit 1 선택 (LOW 활성화)
	_delay_ms(1);  // 1ms 대기

	
	PORTA = ss_data[number / 10];  // 십의 자리 표시
	PORTC = 0x08;  // Digit 2 선택 (LOW 활성화)
	_delay_ms(1);  // 1ms 대기
}

int main(void) {
	unsigned int count = 0;  // 현재 표시할 수
	unsigned char button1_pressed = 0;  // 버튼1 상태
	unsigned char button2_pressed = 0;  // 버튼2 상태
	unsigned char button3_pressed = 0;
	unsigned char prev_button1 = 0;  // 버튼1 이전 상태
	unsigned char prev_button2 = 0;  // 버튼2 이전 상태
	unsigned char prev_button3 = 0;

	init_devices();  // 장치 초기화

	while (1) {
		// 버튼 입력 읽기
		button1_pressed = (PIND & 0x01) == 0x01;  // D0 핀
		button2_pressed = (PIND & 0x02) == 0x02;  // D1 핀
		button3_pressed = (PIND & 0x04) == 0x04;

		// 버튼1: 숫자 증가
		if (button1_pressed && !prev_button1) {
			_delay_ms(200);  // 디바운스
			if (++count > 99) count = 0;  // 99 넘으면 0으로 순환
		}

		// 버튼2: 숫자 감소
		if (button2_pressed && !prev_button2) {
			_delay_ms(200);  // 디바운스
			if (count == 0)
			count = 99;  // 아래로 가면 99 순환
			else
			count--;
		}
		
		
		if (button3_pressed && !prev_button3) {
					_delay_ms(200);  // 디바운스
					count = 0;
				}

		// 버튼 상태 저장
		prev_button1 = button1_pressed;
		prev_button2 = button2_pressed;
		prev_button3 = button3_pressed;

		// 숫자 표시
		display_number(count);
	}

	return 0;
}
