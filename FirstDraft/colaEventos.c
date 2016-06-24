#include <sched.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <pthread.h>

#include "tipos.h"
#include "colaEventos.h"

//// VARIABLES DE ESTE MODULO
#define MAX_EVENTOS 8

static evento_t* buffer[MAX_EVENTOS];
static pthread_mutex_t mutex;
static pthread_cond_t hayElemento, hayHueco;
static int n_elementos;
static int posC;
static int posP;

//////
void initCola() {
	posC = 0;
	posP = 0;
	n_elementos=0;
	pthread_mutex_init(&mutex, NULL); 
  	pthread_cond_init(&hayElemento, NULL); 
  	pthread_cond_init(&hayHueco, NULL); 
}

// Funcion bloqueante: si hay un evento en la cola, 
// se entrega ese evento y se saca de la cola. 
//Si no hay, se queda bloqueada hasta que llegue uno
evento_t* siguienteEvento() {
	evento_t* ev = NULL;
 	pthread_mutex_lock(&mutex);    /* acceder al buffer */
        
	while (n_elementos == 0)       /* si buffer vacio */
            pthread_cond_wait(&hayElemento, &mutex); /* se bloquea */

     ev = buffer[posC];
	//printf("RECIBE EVENTO: %d....",ev);
     posC = (posC + 1) % MAX_EVENTOS;
     n_elementos--;
     pthread_cond_signal(&hayHueco);   /* buffer no lleno */ 
	//printf("DONE\n");
    pthread_mutex_unlock(&mutex);
	return ev;
}

void enviaEvento(evento_t* ev) {
	pthread_mutex_lock(&mutex);       /*acceder al buffer*/        
	while (n_elementos == MAX_EVENTOS) { /*si buffer lleno*/
           	pthread_cond_wait(&hayHueco, &mutex); /*se bloquea*/
	}
	//printf("ENVIA EVENTO: %d.....",ev);
    buffer[posP] = ev;
	posP = (posP + 1) % MAX_EVENTOS;
    n_elementos++;
    pthread_cond_signal(&hayElemento);   /*buffer no vacio*/
	//printf("DONE\n");
	pthread_mutex_unlock(&mutex);
}
