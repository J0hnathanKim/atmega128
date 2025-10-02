#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define DEBOUNCE_DELAY 50  // 디바운싱 딜레이 (ms)
#define MOVE_DELAY 50      // LED 이동 딜레이 (ms)

// 간단한 디바운싱 함수
void debounce(void) {
    _delay_ms(DEBOUNCE_DELAY);
}

int main(void)
{
    // 초기 LED 위치 (PF0)
    int position = 0x01;
    // LED 이동 방향: 0 = 좌측(<<), 1 = 우측(>>)
    short direction = 0;

    DDRF = 0xFF;  // PORTF OUTPUT (LED)
    DDRC = 0x00;  // PORTC INPUT (버튼)

    while (1)
    {
        // 1번 스위치(PC0)가 눌렸는지 확인
        if (PINC & 0x01)
        {
            debounce();  // 디바운싱 처리

            // 디바운싱 후에도 버튼이 눌려 있는지 확인
            if (PINC & 0x01)
            {
                PORTF = position;  // LED 상태 업데이트

                // LED 이동 루프
                while (1)
                {
                    // 방향에 따라 LED 이동
                    switch (direction)
                    {
                        case 0: // 좌측 이동
                            if (position == 0x80)  // PF7에 도달
                            {
                                direction = 1;  // 방향 반전 (우측)
                            }
                            else
                            {
                                position = position << 1;  // 좌측 이동
                            }
                            break;

                        case 1: // 우측 이동
                            if (position == 0x01)  // PF0에 도달
                            {
                                direction = 0;  // 방향 반전 (좌측)
                            }
                            else
                            {
                                position = position >> 1;  // 우측 이동
                            }
                            break;
                    }

                    PORTF = position;  // LED 상태 업데이트

                    // 2번 스위치(PC1)를 누르면 이동 루프 종료
                    if (PINC & 0x02)
                        break;

                    _delay_ms(MOVE_DELAY);  // 이동 딜레이
                }
            }
        }
    }
}
