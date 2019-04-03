#include "motor_driver.h"

// motors use pins

/*
 * IN 1 & IN 2 & EN A
 *
 * IN 3 & IN 4 & EN B
 */

void setA(int speed, wheelDirection direction)
{
    switch (direction)
    {
    case forward:
        setBit(PORTB, H_IN1);
        clearBit(PORTD, H_IN2);
        break;
    case back:
        setBit(PORTD, H_IN2);
        clearBit(PORTB, H_IN1);
        break;
    }
    OCR0B = speed;
}

void setB(int speed, wheelDirection direction)
{
    switch (direction)
    {
    case forward:
        setBit(PORTB, H_IN3);
        clearBit(PORTB, H_IN4);
        break;
    case back:
        setBit(PORTB, H_IN4);
        clearBit(PORTB, H_IN3);
        break;
    }
    OCR0A = speed;
}

void initTimer()
{
    // set both motors to start off
    OCR0A = 0;
    OCR0B = 0;

    // start TCNT0 at 0
    TCNT0 = 0x00;

    // Enable fast pwm mode for DC motor output
    TCCR0A = 0xA3;
    TCCR0B = 0x05; // 1024 prescaler
}

void initMotor()
{
    // Init port B for output
    DDRB = 0xFF;
    PORTB = 0xFF;
    DDRD = 0xFF;

    initTimer();
}

void driveLeft(int speed, wheelDirection direction)
{
    // TODO
}

void driveRight(int speed, wheelDirection direction)
{
    // TODO
}

void driveForward(int speed)
{
    driveLeft(speed, forward);
    driveRight(speed, forward);
}

void driveBackward(int speed)
{
    driveLeft(speed, back);
    driveRight(speed, back);
}
