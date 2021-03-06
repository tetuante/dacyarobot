#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <pthread.h>

#include <wiringPi.h>
#include "fsm.h"
#include "colaEventos.h"
#include "mcp3008.h"
#include "distFrontal.h"
#include "distLateral.h"
#include "motores.h"
#include "encoder.h"

#define MCP3008_SPI_CHANNEL 0


int main() {
	
	pthread_t fronThread, latThread, encoderIzq, encoderDcha;
	printf("Init cola de eventos\n");
	initCola();
	printf("Creo hilo timer y btonera\n");


	// SETUP environment
	wiringPiSetup();
	mcp3008Setup(MCP3008_SPI_CHANNEL);
	setupMotores();
	parar();
	encoderSetup();
	botonSetup();
	
	// hilos para front y lat sensors
	pthread_create(&fronThread, NULL, entryDistanciaFrontal, (void*)NULL);
	pthread_create(&latThread, NULL, entryDistanciaLateral, (void*)NULL);
	
	//hilos para encoders laterales
	pthread_create(&encoderIzq, NULL, entryEncoder,"IZQ" );
        pthread_create(&encoderDcha, NULL, entryEncoder,"DCHA" );
	
//	while(1);

	printf("Invoco FSM\n");
	fsm();
	
	
	printf("RARO: la FSM ha muerto!!!. Salimos\n");	
	mcp3008Close();
	exit(-1);
}
