/*
 *  main,c
 *  leer distancias de dos infrarrojos por SPI usando un MCP300
 *
 * Requires: wiringPi (http://wiringpi.com)
 * Copyright (c) 2015 http://shaunsbennett.com/piblog
 ***********************************************************************
 */
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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

char *usage = "Usage: distancia [-l]";
// -l   = load SPI driver,  default: do not load


void loadSpiDriver()
{
    if (system("gpio load spi") == -1)
    {
        fprintf (stderr, "Can't load the SPI driver: %s\n", strerror (errno)) ;
        exit (EXIT_FAILURE) ;
    }
}

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


int main (int argc, char *argv [])
{
   

    int spiChannel=0;
    int channelConfig=CHAN_CONFIG_SINGLE;

    if (argc > 2)
    {
        fprintf (stderr, "%s\n", usage) ;
        return 1 ;
    }
   
 	
    if ( (argc==2) && ( strcasecmp (argv [1], "-l") == 0 || strcasecmp (argv [1], "-load") == 0 ) ) 
            loadSpiDriver();
       
   
      
    // REALLY THE MAIN THING    
    wiringPiSetup () ;
    spiSetup(spiChannel);
    pinMode(PIN_CNI70_SIGUELINEAS,INPUT);
	
    printf("PROBANDO PROBANDO\n");
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
