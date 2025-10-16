// 예제 1 첫 번째 자리의 7sement의 A, B, C 자리를 돌아가며 점등한다.
//PORTC에 digit을 할당하는 이유 -> digit은 몇 번째 칸의 7segment를 제어할지를 의미한다.
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

// 7-Segment 출력 데이터
char ss_data[8] = {
    0x01, // A
    0x02, // B
    0x04, // C
    0x08, // D
    0x10, // E
    0x20, // F
    0x40, // G
    0x80  // DP
};

// 장치 초기화 함수
void init_devices(void) {
    DDRA = 0xFF; // PORTA: 출력 (7-Segment 데이터)
    DDRC = 0x0F; // PORTC: 하위 4비트 출력 (Digit 선택)
}

int main(void) {
    unsigned int i = 0; // 현재 표시할 숫자
    init_devices();     // 장치 초기화

    while (1) {
        // 모든 Digit 비활성화
        PORTC = 0x0F;

        // 현재 숫자 출력
        PORTA = ss_data[i];
        PORTC = ~0x01; // Digit 선택 (LOW 활성화)

        _delay_ms(1000); // 1초 대기

        // 다음 숫자로 이동
        i++;
        if (i > 7) {
            i = 0; // 다시 0부터 시작
        }
    }

    return 0;
}
