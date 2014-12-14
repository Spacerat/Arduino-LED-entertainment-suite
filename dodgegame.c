#include "LEDlib.h"
#include "stdint.h"
#include "stdlib.h"
#include "input.h"
//#include "serial_lib_interrupt.h"


static uint8_t gmatrix[8];
volatile static uint8_t x = 4;
volatile static uint8_t y = 1;

static uint8_t cavern_w = 5;
static uint8_t cavern_pos = 3;
static long unsigned int counter = 0;
static int lolmode = 0;

static inline uint8_t get_cbits() {
	return ~(((1 << cavern_w) - 1) << cavern_pos);
}

void dodgegame_step(State * s, LEDmatrix* m, const input_t input) {
	uint8_t i;
	//Shift game field up	
	for (i = 0; i < 7; i++) {
		gmatrix[i] = gmatrix[i+1];
	}
	//Move cavern
	int8_t incr = (int8_t) (rand() % 3 - 1);
	cavern_pos = (cavern_pos + incr < 0 || cavern_pos + cavern_w + incr > 8) ? cavern_pos : cavern_pos + incr;
	if (lolmode) {
		gmatrix[7] = (1 << (rand() % 8));
	}
	else {
		gmatrix[7] = get_cbits();
	}
	//Display on LED matrix
	for (i = 0; i < 8; i++) {
		m->matrix[i] = gmatrix[i];
	}
	m->matrix[y] |= (1 << x);
	//Check if player has hit wall
	if (gmatrix[y] & (1 << x)) {
		s->end = 1;
	}
	
	//Increment score counter, increase difficulty
	counter++;
	if (counter % 30 == 0) {
		s->clockdivide = s->clockdivide > 120 ? s->clockdivide - 16 : s->clockdivide;
	}
	if (counter == 30) {
		cavern_w = 4;
	}
	if (counter > 100 && counter < 250) {
		cavern_w = 3 + (rand() % 2);
	}
	else if (counter > 250) {
		cavern_w = 3;
	}
	if (counter % 150 == 0) {
		lolmode = 1;
	}
	if (counter % 170 == 0) {
		lolmode = 0;
	}
}

void dodgegame_click(State * s, LEDmatrix* m, const input_t input, const input_t prev) {
	m->matrix[y] &=~ (1 << x);
	if (input & INPUT_LEFT) {
		x = x == 7 ? x : x + 1;
	}
	else if (input & INPUT_RIGHT) {
		x = x == 0 ? x : x - 1;		
	}
	if (input & INPUT_UP) {
		y = y == 0 ? y : y - 1;
	}
	else if (input & INPUT_DOWN) {
		y = y == 7 ? y : y + 1;
	}
	if (gmatrix[y] & (1 << x)) {
		//Game over!
		s->end = 1;
	}
	m->matrix[y] |= (1 << x);
}

void dodgegame_setup(State * s, LEDmatrix* m) {
	uint8_t i;
	uint8_t cbits = get_cbits();
	x = 4;
	y = 1;
	cavern_w = 5;
	cavern_pos = 3;
	counter = 0;
	lolmode = 0;

	s->clockdivide = 256;
	for (i = 0; i < 8; i++) {
		gmatrix[i] = cbits;
		m->matrix[i] = cbits;
	}
	s->step = dodgegame_step;
	s->click = dodgegame_click;
}
