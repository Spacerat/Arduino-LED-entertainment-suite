#include "LEDlib.h"


//////////---ANIMATION 1---/////////////

void animation1_step(State * s, LEDmatrix* m, const unsigned char input) {
	int i = 0;
	for (i = 0; i < 8; i++) {
		m->matrix[i] <<= 1;
		if (m->matrix[i] == 0) {
			m->matrix[i] = 1;
		}
	}
}

void animation1_click(State * s, LEDmatrix* m, const unsigned char input, const unsigned char prev) {
	if (input & 1) {
		s->step = 0;
	}
}

void animation1_setup(State * s, LEDmatrix* m) {
	int i = 0;
	for (i = 0; i < 8; i++) {
		m->matrix[i] = 1 << i;
	}
	s->step = animation1_step;
	s->click = animation1_click;
}
