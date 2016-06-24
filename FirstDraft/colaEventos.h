#ifndef _COLAEVENTOS_H
#define _COLAEVENTOS_H

#include "tipos.h"

void initCola();
evento_t* siguienteEvento();
void enviaEvento(evento_t* ev);

#endif
