#include <unistd.h>
#include "colaEventos.h"
#include "tipos.h"

void* timerFake(void* arg) {

	while (1) {
		sleep(1);
		enviaEvento(SEGUNDO);
	}
}
