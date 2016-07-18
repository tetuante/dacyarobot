#define _GNU_SOURCE

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

#include <wiringPi.h>
#include "mcp3008.h"
#include "encoder.h"
#include "colaEventos.h"
#include "tipos.h"

/** #define PINDCHA1 0
#define PINDCHA2 3
#define PINDIZQ1 4 
#define PINIZQ2  5
* **/
#define NPINES 4
int pines[NPINES] = {PINDCHADENTRO,PINDCHAFUERA,PINIZQDENTRO,PINIZQFUERA};

void encoderSetup() {
	 // set pin as input
	 int i=0;
	 
	 for (i=0; i<  NPINES; i++)
		pinMode(pines[i],INPUT);

}

void* entryEncoder(void* side) {
	char* rueda = (char*) side;
	int index = 0;
	if ( strcmp(rueda,"IZQ") == 0 )
		index = 2;
		
	int lastRead = 0; // last read 
	int nflancos = 0;	// numero de flancos (de subida; 0 a 1) leidos % NPULSOS
	int niters = 0;
        int curIter = 0;
	 while (1) {  
		int datoDentro = digitalRead(pines[index]);
		int datoFuera = digitalRead(pines[index+1]);
		int lectura = datoDentro + 2*datoFuera;
	//	printf("RUEDA %s dato dentro %d dato fuera %d\n",rueda, datoDentro,datoFuera);
		switch (lectura) {
			case 0:
				if (lastRead == 1 ) lastRead =0;
				break;
			case 1:
			case 2:
			        //printf("ERROR leyendo encoder %s > valor %d\n",rueda, lectura);
	                case 3:
				if (lastRead == 0 ) {
					lastRead = 1;
					nflancos++;
                                        if (nflancos % 32 == 0) niters++;
				}
				break;

		}
		delay(5);
		
		if ( (nflancos >0) && ( (nflancos % NPULSOS) == 0 ) )
			printf("RUEDA %s VUELTA %d \n",rueda, niters);
	
    }	    
	
	
	
}
