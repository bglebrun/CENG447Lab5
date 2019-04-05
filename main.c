#define F_CPU 16000000
#include "motor_driver.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

// interrupt counter for motor A
volatile unsigned long MAIC;
// number of interrupts to stop driving after
unsigned long targetCount;

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
        driveForward(128, 750);
        stop();
        turnLeft(128, 500);
        stop();
    }
    driveForward(128, 750);
}

void testCircle()
{
    for (int i = 0; i < 100; i++)
    {
        driveForward(64, 200);
        turnLeft(64, 200);
    }
}

int main()
{
    // int i = 0;
    Init();
    while (1)
    {
        // requirement 2: drive forward at full-speed for 2 seconds
        driveForward(255, 2000);
        _delay_ms(500);
        // requirement 3: drive backwards at half-speed for 4 seconds
        driveBackward(128, 4000);
        _delay_ms(500);
        // requirement 4: turn in place counter-clockwise at full-speed 2
        // seconds
        turnLeft(255, 2000);
        _delay_ms(500);
        // requirement 5: turn in place clockwise at half-speed for 4 seconds
        turnRight(128, 4000);
        _delay_ms(500);
        // requirement 6: approximate a square path
        testSquare();
        _delay_ms(500);
        // requirement 7: approximate a circular path
        testCircle();
        _delay_ms(500);
    }
    return 1;
}

ISR(TIMER0_COMPA_vect) { MAIC++; }
