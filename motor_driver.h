#ifndef _MOTOR_DRIVER_H_
#define _MOTOR_DRIVER_H_
#include "bit_macros.h"
#include "pin_map.h"
#include "util/delay.h"
#include <avr/io.h>

#define TURN_DELAY_CIRCLE 250
#define TURN_DELAY_SQUARE 500
#define DRIVE_DELAY 500

typedef enum WHEEL_DIRECTION
{
    FORWARD = 0,
    BACK
} wheelDirection;

void initMotor();
void setB(unsigned char speed, wheelDirection direction);
void setA(unsigned char speed, wheelDirection direction);
void stop();
void turnLeft(unsigned char speed, int time_ms);
void turnRight(unsigned char speed, int time_ms);
void driveForward(unsigned char speed, int time_ms);
void driveBackward(unsigned char speed, int time_ms);
void delayUntilTargetCount();
void getNumInterruptsForDuration(int duration_ms);

#endif
