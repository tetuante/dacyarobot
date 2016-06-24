#ifndef _CONTROL_SERVO_H
#define _CONTROL_SERVO_H

#include "tipos.h"

#define PIN_SERVOIZQ 1
#define PIN_SERVODCHA 2

#define PWM_RANGE 200
// PARALLAX: periodo de 20ms. Parado a 1.5ms -> 7.5% duty cycle
//#define PWM_STOP 15 
#define PWM_STOP 0
#define PWM_MAX_FORWAD 17
#define PWM_MAX_BACK   13


void adelanteServo(direccion_t servo);
void pararServo(direccion_t servo); 
void atrasServo(direccion_t servo);
int setupServo(direccion_t servo);

#endif
