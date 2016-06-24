#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>
#include <stdlib.h>

#define PIN_SERVOIZQ 1
#define PIN_SERVODCHA 2
#define PWM_RANGE 200
// PARALLAX: periodo de 20ms. Parado a 1.5ms -> 7.5% duty cycle
#define PWM_STOP 15
#define PWM_MAX_FORWAD 17
#define PWM_MAX_BACK   13

int main() {
	int tecla;
	
	wiringPiSetup();
	pinMode(PIN_SERVODCHA,OUTPUT);
	pinMode(PIN_SERVOIZQ,OUTPUT);

	if (softPwmCreate(PIN_SERVODCHA,0,PWM_RANGE) != 0) {
		printf("ERROR en softPwmCreate:\n");
		exit(-1);
	}
	if (softPwmCreate(PIN_SERVOIZQ,0,PWM_RANGE) != 0) {
		printf("ERROR en softPwmCreate:\n");
		exit(-1);
	}
	
	printf("CALIBRATE: haz que se paren\n");
	softPwmWrite(PIN_SERVODCHA, PWM_STOP);
	softPwmWrite(PIN_SERVOIZQ, PWM_STOP);
	
	printf("Pulsa cualquier tecla cuando este calibrado:");
	scanf("%d",&tecla);
	printf("Calibrado terminado. Pulsaste %d\n",tecla);
	softPwmWrite(PIN_SERVODCHA, PWM_MAX_FORWAD);
	softPwmWrite(PIN_SERVOIZQ, PWM_MAX_BACK);

	delay(5000);
	while (1) {
		/*
		scanf("%d",&tecla);
		printf("Valor introducido %d\n",tecla);
		softPwmWrite(PIN_SERVODCHA, tecla);
		delay(5000);
		*/
		/*
		softPwmWrite(PIN_SERVODCHA, PWM_MAX_FORWAD);
		delay(5000);
		softPwmWrite(PIN_SERVODCHA, PWM_MAX_FORWAD-1);
		delay(5000);
		softPwmWrite(PIN_SERVODCHA, PWM_MAX_FORWAD-2);
		delay(5000);
		softPwmWrite(PIN_SERVODCHA, PWM_MAX_FORWAD-3);
		delay(5000);
		softPwmWrite(PIN_SERVODCHA, PWM_MAX_FORWAD-4);
		delay(5000);
		* */
	}
}
