#include "LEDlib.h"
#include "letters.c"
#include "string.h"


//////////---ANIMATION 1---/////////////
const unsigned char* letters[] = {_A,_B,_C,_D,_E,_F,_G,_H,_I,_J,_K,_L,_M,_N,_O,_P,_Q,_R,_S,_T,_U,_V,_W,_X,_Y,_Z,_COL,_DASH,_BRA2,__, _FULL, _CHECK, _B2, _TEMP, _LINE, _SMILE, _DOT, _COLDOT};

unsigned int k = 0;
int go = 1;

void animation2_step(State * s, LEDmatrix* m, const unsigned char input) {
	if (go) {
		memcpy(m->matrix, letters[k], 8);
		k = (k + 1) % 38;
	}
}

void animation2_click(State * s, LEDmatrix* m, const unsigned char input, const unsigned char prev) {
	if (input & 1) {
		s->step = 0;
	}
	else if ((input & 2) != (prev & 2) && (input & 2)){
		go = 1 - go;
	}
}

void animation2_setup(State * s, LEDmatrix* m) {
	int i = 0;
	memcpy(m->matrix, letters[k], 8);
	s->step = animation2_step;
	s->click = animation2_click;
}
