#define F_CPU 16000000
// #define __AVR_ATmega328P__
#include "motor_driver.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

// interrupt counter for motor A
volatile long MAIC;
// number of interrupts to stop driving after
long targetCount;

void Init()
{
    // Enable global interrupts
    initMotor();

    sei();
}

void testCircle()
{
    for (int i = 0; i < 3; i++)
    {
        driveForward(128, 500);
        _delay_ms(200);
        turnLeft(128, 250);
        _delay_ms(200);
    }
}

int main()
{
    // int i = 0;
    Init();
    while (1)
    {
        testCircle();
    }
    return 1;
}

ISR(TIMER0_COMPA_vect) { MAIC++; }
