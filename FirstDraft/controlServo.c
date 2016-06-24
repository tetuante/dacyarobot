#include "controlServo.h"
#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>
#include <stdlib.h>


int getPin(direccion_t servo) {
	int pin;
	if ( servo == IZQUIERDA ) {
		pin = PIN_SERVOIZQ;
	}
	else {
		pin = PIN_SERVODCHA;
	}
	return pin;
}

int getForwardDir(direccion_t servo) {

	if ( servo == IZQUIERDA ) {
		return PWM_MAX_FORWAD ;
	}
	else {
		return PWM_MAX_BACK;
	}
}

int getBackDir(direccion_t servo) {

	if ( servo == IZQUIERDA ) {
		return PWM_MAX_BACK ;
	}
	else {
		return PWM_MAX_FORWAD;
	}
}

void adelanteServo(direccion_t servo) {
	int pin = getPin(servo);
	
	softPwmWrite(pin, getForwardDir(servo));	
}

void pararServo(direccion_t servo) {
	int pin = getPin(servo);
	softPwmWrite(pin, PWM_STOP);
}

void atrasServo(direccion_t servo) {
	int pin = getPin(servo);
	softPwmWrite(pin, getBackDir(servo));
}

int setupServo(direccion_t servo) {
	int pin = getPin(servo);
	pinMode(pin,OUTPUT);
	if (softPwmCreate(pin,0,PWM_RANGE) != 0) {
			printf("ERROR en softPwmCreate:\n");
			return -1;
	}
	softPwmWrite(pin, PWM_STOP);	
	return 0;
}
