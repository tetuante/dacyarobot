#define _GNU_SOURCE

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

#include <wiringPi.h>
#include "mcp3008.h"
#include "boton.h"
#include "colaEventos.h"
#include "tipos.h"

unsigned int lastInt=0; //tie of las interrupt
#define MILIS_BTW_INT 500
void tratarBoton() {
		printf("RECIBIDA INTERRUPCION\n");
		unsigned int now = millis();
		if ( (now - lastInt) > MILIS_BTW_INT ) {
			evento_t* boton;
			boton = (evento_t*) malloc(sizeof(evento_t));
			boton->tipo = BOTON;
			boton->data = 0;		
			enviaEvento(boton);
		}
		lastInt = now;
}

void botonSetup() {
	/*
	pinMode(BOTONPIN,INPUT);
	printf("LEYENDO....\n");
	int i;
	for (i=0;i<20;i++) {
		int a = digitalRead(BOTONPIN);
		printf("Leido boton %d\n",a);
		delay(500);
	}
	*/
	printf("CONFIGURO INT\n");
	wiringPiISR(BOTONPIN,INT_EDGE_RISING, tratarBoton);
}

