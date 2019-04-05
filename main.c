#define F_CPU 16000000
#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)
// #define __AVR_ATmega328P__
#include "motor_driver.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

// interrupt counter for motor A
volatile long MAIC;
// number of interrupts to stop driving after
long targetCount;

void initUART();

void Init()
{
    // setup UART to allow output to screen
    initUART();
    // setup motor controller PWM
    initMotor();
    // Enable global interrupts
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

void initUART()
{
    // init uart
    UCSR0B |= 0x98;
    UCSR0C |= 0x06;
    UBRR0L = BAUD_PRESCALE;
    UBRR0H = (BAUD_PRESCALE >> 8);
}

ISR(TIMER0_COMPA_vect) { MAIC++; }
