// 예제 1-3 첫번째 자리에서 0, 두번째 자리에 1, 세번째 자리에 2, 네번째 자리에 3, 첫번째 자리에 4.....
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

// 7-Segment 출력 데이터
char ss_data[10] = {
	0x3F, 
	0x06, 
	0x5B, 
	0x4F, 
	0x66, 
	0x6D, 
	0x7D, 
	0x27,  
	0x7F,
	0x67
};

// 장치 초기화 함수
void init_devices(void) {
	DDRA = 0xFF; // PORTA: 출력 (7-Segment 데이터)
	DDRC = 0x0F; // PORTC: 하위 4비트 출력 (Digit 선택)
}

int main(void) {
	unsigned int i = 0; // 현재 표시할 숫자
	uint8_t digit = 0x01;
	init_devices();     // 장치 초기화

	while (1) {
		// 모든 Digit 비활성화
		PORTC = 0x0F;

		// 현재 숫자 출력
		PORTA = ss_data[i];
		PORTC = ~digit; // Digit 선택 (LOW 활성화)

		_delay_ms(1000); // 1초 대기

		// 다음 숫자로 이동
		i++;
		if (i > 9) {
			i = 0; // 다시 0부터 시작
		}
			
			digit=digit << 1;
			if(digit > 0x08){
				digit = 0x01;
			}
		
	}

	return 0;
}
