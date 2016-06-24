#define _GNU_SOURCE

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

#include <wiringPi.h>
#include "mcp3008.h"
#include "distFrontal.h"
#include "colaEventos.h"
#include "tipos.h"

// periodo de muestreo en ms
static int samplePeriod = 200;


void* entryDistanciaFrontal(void* arg)
{
  
	printf("Entry Distancia Frontal\n");
    while (1) {  
	
		unsigned tic = millis();
		int distDcha = myAnalogRead(INFRA_FRONT_DCHA);
		
		int distIzq = myAnalogRead(INFRA_FRONT_IZQ);
		//printf("Hilo frontal. Dcha: %d Izq: %d \n",distDcha,distIzq);
		
		// crear eventos para el controlador
		evento_t* evizq;
		evizq = (evento_t*) malloc(sizeof(evento_t));
		evizq->tipo = DFRONTIZQ;
		evizq->data = distIzq;
		
		evento_t* evdcha;
		evdcha = (evento_t*) malloc(sizeof(evento_t));
		evdcha->tipo = DFRONTDCHA;
		evdcha->data = distDcha;
		
		enviaEvento(evizq);
		enviaEvento(evdcha);
		unsigned toc = millis();
		
		// Espera al siguiente muestreo
		if ( (toc-tic) < samplePeriod) 	
			delay(samplePeriod - (toc-tic));
		else
			fprintf(stderr, "ERROR: miss FRONT period!!");					
    }	    

    return 0;
}
