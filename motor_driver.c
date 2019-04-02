#include "motor_driver.h"

void initMotor() {
  // Init port B for output
  DDRB = 0xFF;
  PORTB = 0xFF;
  DDRD = 0xFF;

  OCR0A = 0;

  // Enable fast pwm mode for DC motor output
  TCCR0A = 0xA3;
  TCCR0B = 0x05;

  // TCNT0 to 0
  TCNT0 = 0x00;
  // TODO: this probably isn't correct
  // output compare B registers to approximately 75% duty cycle (div by 255)
  // Shows as constant square wave, in reality this will be changed (probably)
  OCR0B = 192;
}

void driveLeft(int speed, wheelDirection direction) {
    // TODO
}

void driveRight(int speed, wheelDirection direction) {
    // TODO
}

void driveForward(int speed) {
    driveLeft(speed, forward);
    driveRight(speed, forward);
}

void driveBackward(int speed) {
    driveLeft(speed, back);
    driveRight(speed, back);
}