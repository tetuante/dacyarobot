#define _GNU_SOURCE

#include <unistd.h>
#include "colaEventos.h"
#include "tipos.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

#include <wiringPi.h>
#include <wiringPiSPI.h>

#define	TRUE	            (1==1)
#define	FALSE	            (!TRUE)
#define CHAN_CONFIG_SINGLE  8
#define CHAN_CONFIG_DIFF    0

#define PIN_CNI70_SIGUELINEAS 0

static int myFd ;



void spiSetup (int spiChannel)
{
    if ((myFd = wiringPiSPISetup (spiChannel, 1000000)) < 0)
    {
        fprintf (stderr, "Can't open the SPI bus: %s\n", strerror (errno)) ;
        exit (EXIT_FAILURE) ;
    }
}

int myAnalogRead(int spiChannel,int channelConfig,int analogChannel)
{
    if(analogChannel<0 || analogChannel>7)
        return -1;
    unsigned char buffer[3] = {1}; // start bit
    buffer[1] = (channelConfig+analogChannel) << 4;
    wiringPiSPIDataRW(spiChannel, buffer, 3);
    return ( (buffer[1] & 3 ) << 8 ) + buffer[2]; // get last 10 bits
}


void* entryDistanciaFrontal(void*)
{
   

    int spiChannel=0;
    int channelConfig=CHAN_CONFIG_SINGLE;
       
    printf("Cargando modulo \n"); 
    spiSetup(spiChannel);
    pinMode(PIN_CNI70_SIGUELINEAS,INPUT);
	
    while (1) {  
	int distChan0 = myAnalogRead(spiChannel,channelConfig,0);
	int distChan1 = myAnalogRead(spiChannel,channelConfig,1);
	int sigueL = digitalRead(PIN_CNI70_SIGUELINEAS);
	printf(" Canal 0: %d Canal 1: %d SigueL: %d\n",distChan0,distChan1,sigueL);
	delay(500);
	
    }	    


    close (myFd) ;
    return 0;
}






void* botonFake(void* arg) {
	int c;
	while (1) {
		//printf("ME PONGO A LEER EL TECLADO\n");
		//c = getchar_unlocked();
		c = getchar();
		//printf("LEIDO\n");
		switch (c) {
			case '1': 
				enviaEvento(BOTON1);
				break;
			case '2':
				enviaEvento(BOTON2);
				break;
			default:
				break;
		}	
	}
}

