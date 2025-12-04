#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRE = 0xFF;

    TCCR3A = 0xAA;  // COM3A1, COM3B1, COM3C1 set, WGM31 set
    TCCR3B = 0x1B;  // WGM33, WGM32 set, CS31, CS30 set

    ICR3 = 4999;   // 5000 tick (20ms 주기)

    int startCnt = 149;
    int endCnt = 600;

    while (1)
    {
        for (int i = startCnt; i < endCnt; i++)
        {
            OCR3A = i;      // PE3 (OC3A) 출력
            OCR3B = i*2;    // PE4 (OC3B) 출력
            OCR3C = i*4;    // PE5 (OC3C) 출력
            _delay_ms(10);
        }
    }

    return 0;
}
