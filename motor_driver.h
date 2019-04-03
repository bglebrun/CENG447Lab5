#ifndef _MOTOR_DRIVER_H_
#define _MOTOR_DRIVER_H_
#include "bit_macros.h"
#include "pin_map.h"
#include <avr/io.h>

typedef enum WHEEL_DIRECTION
{
    FORWARD = 0,
    BACK
} wheelDirection;

void initTimer();
void initMotor();
void driveLeft(int speed, wheelDirection direction);
void driveRight(int speed, wheelDirection direction);
void driveForward(int speed);
void driveBackward(int speed);

#endif
