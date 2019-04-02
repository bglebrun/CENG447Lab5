#ifndef _MOTOR_DRIVER_H_
#define _MOTOR_DRIVER_H_
#include "pin_map.h"
#include "bit_macros.h"
#include <avr/io.h>

typedef enum wheelDirection {
    forward = 0,
    back
} wheelDirection;

void initMotor();
void driveLeft(int speed, wheelDirection direction);
void driveRight(int speed, wheelDirection direction);
void driveForward(int speed);
void driveBackward(int speed);

#endif