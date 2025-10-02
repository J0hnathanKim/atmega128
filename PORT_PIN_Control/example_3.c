#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define DEBOUNCE_DELAY 50 // 디바운싱 딜레이 (ms)

// 간단한 디바운싱 함수
void debounce(void) {
	_delay_ms(DEBOUNCE_DELAY);
}

int main(void)
{
	DDRF = 0xFF; // PORTF를 OUTPUT으로 설정 (LED)
	DDRC = 0x00; // PORTC를 INPUT으로 설정 (버튼)

	int flag = 0; // LED 상태를 기억하는 플래그

	while (1)
	{
		// PC0 버튼이 눌렸는지 확인
		if (PINC & 0x01)
		{
			debounce(); // 디바운싱 처리

			// 디바운싱 후에도 버튼이 눌려 있는지 확인
			if (PINC & 0x01)
			{
				// flag가 0이면 LED 켜기
				if (flag == 0)
				{
					PORTF = 0xFF; // LED 켜기
					flag = 1;
				}
				// flag가 1이면 LED 끄기
				else
				{
					PORTF = 0x00; // LED 끄기
					flag = 0;
				}

				// 버튼이 계속 눌려 있는 동안 대기 (플래그 한 번만 토글)
				while (PINC & 0x01)
				{
					// 대기
				}
			}
		}

		_delay_ms(50); // 메인 루프에서 짧은 딜레이
	}
}
