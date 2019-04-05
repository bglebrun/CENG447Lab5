#define F_CPU 16000000
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
    // setup motor controller PWM
    initMotor();
    // Enable global interrupts
    sei();
}

void testSquare()
{
    for (int i = 0; i < 3; i++)
    {
        driveForward(64, 750);
        stop();
        turnLeft(64, 750);
        stop();
    }
}

void testCircle()
{
    driveForward(64, 200);
    turnLeft(64, 200);
}

int main()
{
    // int i = 0;
    Init();
    while (1)
    {
        // testSquare();
        // _delay_ms(1000);
        // testCircle();
        // _delay_ms(1000);
        setA(128, FORWARD);
    }
    return 1;
}

ISR(TIMER0_COMPA_vect) { MAIC++; }
