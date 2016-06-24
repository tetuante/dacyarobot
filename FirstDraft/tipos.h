#ifndef _TIPOS_H
#define _TIPOS_H

typedef enum {PARADO=0,CIRCULANDO ,NUM_ESTADOS} estado_t;

// IMPORTANTE: dejar los 4 sensores infrared los primeros porque indexan el array map
//typedef enum {DFRONTIZQ=0,DFRONTDCHA,DLATDCHA, DLATIZQ, ENCODER, NUM_EVENTOS} eventType_t;
typedef enum {DLATIZQ=0,DFRONTIZQ=1 , DFRONTDCHA=2,DLATDCHA=3, ENCODER, NUM_EVENTOS} eventType_t;
typedef enum {IZQUIERDA = 0, DERECHA =1 } direccion_t;

typedef struct _event_t {
		eventType_t tipo;
		int data;
}evento_t;


typedef enum {FALSE,TRUE} bool;


#endif
