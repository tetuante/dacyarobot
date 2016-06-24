
#include "motores.h"
#include "tipos.h"
#include "controlServo.h"

// return 0 if ok, -1 to -3 if error
int setupMotores() {
	int ok1, ok2;
	ok1 = setupServo(IZQUIERDA);
	ok2 = setupServo(DERECHA);
	return (ok1 + 2*ok2);
}

void adelante() {
	adelanteServo(IZQUIERDA);
	adelanteServo(DERECHA);
}

void atras() {
	atrasServo(IZQUIERDA);
	atrasServo(DERECHA);
}

void parar() {
	pararServo(IZQUIERDA);
	pararServo(DERECHA);
}

void izquierda() {
	atrasServo(IZQUIERDA);
	adelanteServo(DERECHA);
	
}
void derecha() {
	adelanteServo(IZQUIERDA);
	atrasServo(DERECHA);
}
