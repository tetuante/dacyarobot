#include "tipos.h"
#include "colaEventos.h"
#include <stdlib.h>
#include <stdio.h>
#include "motores.h"
#include <wiringPi.h>

/// EN ESTE MODULO ESTA LA FSM  Y EL CODIGO ENCARGADO DE MANTENER LA HORA
char* event2string(eventType_t ev) {
	switch (ev)  {
			case DFRONTIZQ:
				return "Frontal izquierda";
			case DFRONTDCHA:
				return "Frontal derecha";
			case DLATIZQ:
				return "Lateral izquierda";	
			case DLATDCHA:
				return "Lateral derecha";	
			default:
				 return "Desconocido";			
		}
}

// tiempo en stop (en ms)
#define _TIEMPO_INICIAL_STOP_ 20
#define UMBRAL 400

// indexado con evetType
// {DLATIZQ=0,DFRONTIZQ=1 , DFRONTDCHA=2,DLATDCHA=3,
unsigned char mapa[] = {0,0,0,0};

void processDistance(eventType_t sensor, int val) {
	if (val < UMBRAL )
		mapa[sensor] = 0;
	else	
		mapa[sensor] = 1; //idea: 
}

void movimiento() {
	//get a single number
    int sensor;
	int val=0;
	for (sensor=DLATIZQ; sensor<=DLATDCHA;sensor++) 
        val |= (mapa[sensor] << sensor);
	
	
	switch (val) {
		case 0:
			adelante();
			break;
		case 1:
		case 2:
		case 3:
			derecha();
			break;
		case 4:
		case 8:
		case 12:
			izquierda();
			break;
		default:
			 atras();
			 break;
	}
	
}	
	

int fsm() {
	evento_t* ev = NULL;
	estado_t estadoActual;
	unsigned int start_time;
	unsigned int current_time;
	
	estadoActual = PARADO;
	//printf("FSM: start loop\n");	
	start_time = millis();
	while (1) {
	
		ev = siguienteEvento(); // llamada bloqueante	
		if (ev == NULL) {
				fprintf(stderr, "ERROR: evento desconocido recibido\n");
				continue; 
		}	
		
		switch (estadoActual) {

			case PARADO:
				parar();
				switch (ev->tipo) {
					case DFRONTIZQ:
					case DFRONTDCHA:
					case DLATIZQ:
					case DLATDCHA:
						//printf("FSM: recibido evento %s. Distancia: %d\n",event2string(ev->tipo),ev->data);
						processDistance(ev->tipo,ev->data);
						break;		
					case BOTON:
						estadoActual = CIRCULANDO;			
					default:
						break;			
				}
				/*
				current_time = millis();
				if (current_time - start_time >  _TIEMPO_INICIAL_STOP_) {
					estadoActual = CIRCULANDO;
					//printf("PASAMOS A CIRCULAR\n");
				}
				*/
				break;

			case CIRCULANDO:	
				switch (ev->tipo) {
					case DFRONTIZQ:
					case DFRONTDCHA:
					case DLATIZQ:
					case DLATDCHA:
						//printf("FSM: recibido evento %s. Distancia: %d\n",event2string(ev->tipo),ev->data);
						processDistance(ev->tipo,ev->data);
						break;
					case BOTON:
						estadoActual = PARADO;
						parar();				
					default:
						break;			
				}
				movimiento();			
				break;		

			default:
				//printf("ESTADO DESCONOCIDO!!. Vuelvo al inicial\n");
				estadoActual = PARADO;
				break;
		}
		
		// Nos encargamos de liberar memoria
		if (ev != NULL) 
			free(ev);
	
	}


}
