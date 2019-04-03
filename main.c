#define F_CPU 16000000
#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)
#include "motor_driver.h"
#include <avr/io.h>
#include <util/delay.h>

void Init()
{
    // Enable global interrupts
    initMotor();

    sei();
}

int main()
{
    // int i = 0;
    Init();
    while (1)
    {
        setA(128, FORWARD);
        _delay_ms(500);
        setA(0, FORWARD);
        _delay_ms(500);
        // From example, OCR0A here is changing constantly from 0 - 100 - 0
        // for(i=0;i<=255;i++){
        //   OCR0A = i;
        //   _delay_ms(10);
        // }
        // for(;i>=0;i--){
        //   OCR0A = i;
        //   _delay_ms(10);
        // }
    }
    return 1;
}
