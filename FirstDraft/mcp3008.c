
#include <pthread.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>

#define	TRUE	            (1==1)
#define	FALSE	            (!TRUE)
#define CHAN_CONFIG_SINGLE  8
#define CHAN_CONFIG_DIFF    0


static int myFd ;
static int __spiChannel=0;
static pthread_mutex_t mutexMCP;
int channelConfig=CHAN_CONFIG_SINGLE;


void mcp3008Setup(int spiChannel)
{
	printf("INIT MCP3008\n");
    if ((myFd = wiringPiSPISetup (spiChannel, 1000000)) < 0)
    {
        fprintf (stderr, "Can't open the SPI bus: %s\n", strerror (errno)) ;
        exit (EXIT_FAILURE) ;
    }
    __spiChannel = spiChannel;
    pthread_mutex_init(&mutexMCP, NULL); 
    
}

void mcp3008Close() {
	close(myFd);
}

//MUST BE a thread safe function sicne could be called from
//different threads to read different analago channels
int myAnalogRead(int analogChannel)
{
	
    if(analogChannel<0 || analogChannel>7)
        return -1;
        
    unsigned char buffer[3] = {1}; // start bit
    buffer[1] = (CHAN_CONFIG_SINGLE+analogChannel) << 4;
    
    pthread_mutex_lock(&mutexMCP); 
    wiringPiSPIDataRW(__spiChannel, buffer, 3);
    pthread_mutex_unlock(&mutexMCP); 
    
    return ( (buffer[1] & 3 ) << 8 ) + buffer[2]; // get last 10 bits
}
