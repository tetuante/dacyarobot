#ifndef __ENCODER__
#define __ENCODER__

#define RADIO
#define NPULSOS 32

/// USING 4 GPIOS for the encoders
#define PINDCHADENTRO 0
#define PINDCHAFUERA 3
#define PINIZQDENTRO 4 
#define PINIZQFUERA  5

// Init function. Must be just called once
void encoderSetup();

void* entryEncoder(void* side);

#endif
