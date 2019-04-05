#include "motor_driver.h"
#include <stdio.h>

// motors use pins

/*
 * IN 1 & IN 2 & EN A
 *
 * IN 3 & IN 4 & EN B
 */

#define DELAY_COUNT(time, rate) time / rate + (time % rate == 0 ? 0 : 1)

// interrupt counter for motor A
volatile extern long MAIC;
extern long targetCount;

static int uart_putchar(char c, FILE* stream);

/* stdout stream */
static FILE mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);

static int uart_putchar(char c, FILE* stream)
{
    if (c == '\n')
        uart_putchar('\r', stream);
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = c;
    return 0;
}

void setA(int speed, wheelDirection direction)
{
    switch (direction)
    {
    case FORWARD:
        setBit(PORTD, H_IN1);
        clearBit(PORTB, H_IN2);
        break;
    case BACK:
        setBit(PORTB, H_IN2);
        clearBit(PORTD, H_IN1);
        break;
    }
    OCR0A = speed;
}

void setB(int speed, wheelDirection direction)
{
    switch (direction)
    {
    case BACK:
        setBit(PORTB, H_IN3);
        clearBit(PORTB, H_IN4);
        break;
    case FORWARD:
        setBit(PORTB, H_IN4);
        clearBit(PORTB, H_IN3);
        break;
    }
    OCR0B = speed;
}

void initMotor()
{
    // Init port B for output
    DDRB = 0xFF;
    DDRD = 0xFF;
    PORTB = 0x00;
    PORTD = 0x00;

    // set both motors to start off
    OCR0A = 0;
    OCR0B = 0;

    // start TCNT0 at 0
    TCNT0 = 0x00;

    // Enable fast pwm mode for DC motor output
    TCCR0A = 0xA3;
    TCCR0B = 0x05; // 1024 prescaler

    // Enable counter match interrupt for counter A
    TIMSK0 = 0x02;
}

void turnLeft(int speed, int time_ms)
{
    getNumInterruptsForDuration(time_ms);
    setB(speed, FORWARD);
    setA(speed, BACK);
    delayUntilTargetCount();
    setB(0, FORWARD);
    setA(0, BACK);
}

void turnRight(int speed, int time_ms)
{
    getNumInterruptsForDuration(time_ms);
    setB(speed, BACK);
    setA(speed, FORWARD);
    delayUntilTargetCount();
    setB(0, BACK);
    setA(0, FORWARD);
}

void driveForward(int speed, int time_ms)
{
    getNumInterruptsForDuration(time_ms);
    setA(speed, FORWARD);
    setB(speed, FORWARD);
    delayUntilTargetCount();
    setB(0, FORWARD);
    setA(0, FORWARD);
}

void driveBackward(int speed, int time_ms)
{
    getNumInterruptsForDuration(time_ms);
    setA(speed, BACK);
    setB(speed, BACK);
    delayUntilTargetCount();
    setB(0, BACK);
    setA(0, BACK);
}

void delayUntilTargetCount()
{
    while (MAIC <= targetCount)
    {
        fprintf(&mystdout, "MAIC: %ld | targetCount: %ld\r\n", MAIC,
                targetCount);
    };
    MAIC = 0;
}

void getNumInterruptsForDuration(int duration_ms)
{
    int prescaler_choice = TCCR0B & 0x07;

    switch (prescaler_choice)
    {
    case 0: // no clock...no motor???
        // ERROR: without a clock a) the motors aren't running and
        // b) we can't wait a duration...
        targetCount = 0;
        break;
    case 1: // 1 prescaler, one interrupt ~ every 0.02ms
        targetCount = DELAY_COUNT(100 * duration_ms, 2);
        break;
    case 2: // 8 prescaler, one interrupt ~ every 0.1ms
        targetCount = DELAY_COUNT(10 * duration_ms, 1);
        break;
    case 3: // 64 prescaler, one interrupt ~ every 1ms
        targetCount = DELAY_COUNT(duration_ms, 1);
        break;
    case 4: // 256 prescaler, one interrupt ~ every 4ms
        targetCount = DELAY_COUNT(duration_ms, 4);
        break;
    case 5: // 1024 prescaler, one interrupt ~ every 16ms
        targetCount = DELAY_COUNT(duration_ms, 16);
        break;
    case 6:
    case 7:
        targetCount = 0;
        // ERROR: 6 and 7 are external clocks and we can't predict them
    }
}
