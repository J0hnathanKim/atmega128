// 예제 2 => 1XXX X2XX XX3X XXX4가 아주 빠르게 진행됨.
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

// 7-Segment 출력 데이터
uint8_t ss_data[10] = {
	0x3F, 
	0x06, 
	0x5B, 
	0x4F, 
	0x66, 
};

// 장치 초기화 함수
void init_devices(void) {
	DDRA = 0xFF; // PORTA: 출력 (7-Segment 데이터)
	DDRC = 0x0F; // PORTC: 하위 4비트 출력 (Digit 선택)
}

int main(void) {
	
	init_devices();     // 장치 초기화
    uint8_t digit_num[4] = {1, 2, 3, 4};
	
	while (1) {
		for(int d = 0; d < 4; d++){
		  PORTC = ~(1 << d);
		  PORTA = ss_data[digit_num[d]];
		  _delay_ms(100);
		}
		
			
	}


}
