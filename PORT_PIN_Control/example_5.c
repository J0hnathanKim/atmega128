#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdlib.h>

int main(void)
{
	DDRF = 0xFF;   // PORTF를 OUTPUT으로 설정
	DDRC = 0x00;   // PORTC를 INPUT으로 설정

	uint8_t led_pattern = 0x00;  // 현재 LED 상태
	uint8_t prev_seed = 0x00;   // 이전 시드 저장

	while(1)
	{
		// PORTC 입력값 읽어서 난수 시드 초기화
		uint8_t seed = PINC;

		// 시드가 바뀌면 LED 모두 끄고 2초 대기
		if(seed != prev_seed)
		{
			PORTF = 0x00;       // LED 모두 끄기
			_delay_ms(2000);    // 2초 대기
			prev_seed = seed;   // 새로운 시드로 초기화
			srand(seed);        // 난수 시드 초기화
			led_pattern = 0x00; // 랜덤 시작 전 상태 초기화
		}

		// 랜덤 LED 토글
		uint8_t rand_bit = 1 << (rand() % 8);
		led_pattern ^= rand_bit;

		PORTF = led_pattern;    // LED 출력
		_delay_ms(500);         // 0.5초 대기
	}
}
