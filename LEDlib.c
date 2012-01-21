//TODO: split LED Matrix and Game State functionality in to separate libraries.

#include "LEDlib.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdint.h>

#include "input.h"

#define TICKPIN PINB4
#define RESETPIN PINB5


/*
	Initialises an LED matrix struct and prepares the board to output to the matrix.
	Sets pins 2-9 and the clock/reset pins as output, and sends the reset signal.
*/
void matrix_setup(LEDmatrix *m) {
	int i;
	//Set digital pins 2 to 9 as output
	DDRD = 0xFC;
	DDRB = 0x03;
	//Set up reset and clock ports as output
	DDRB |= (1 << RESETPIN);
	DDRB |= (1 << TICKPIN);
	
	//Send reset signal
	PORTB |= (1 << RESETPIN);
	_delay_ms(20);
	PORTB &= ~(1 << RESETPIN);
	_delay_ms(10);
	

	//Blank matrix;
	m->row = 0;
	m->clock = 0;
	for (i = 0; i < 8; i++) {
		m->matrix[i] = 0;
	}
}

void matrix_clear(LEDmatrix *m) {
	int i;
	for (i = 0; i < 8; i++) {
		m->matrix[i] = 0;
	}
}

State *state_create(state_func setup, LEDmatrix* m) {
	State *s;
	s = (State*)malloc(sizeof(State));
	//Misc
	s->clockdivide = 128;
	s->counter = 0;
	s->end = 0;
	//User Setup
	matrix_clear(m);
	if (setup) setup(s, m);
	return s;
}
/*
	This function toggles the "clock" signal sent to the 8 bit octal counter
	and - on the rising clock - displays the next row in the matrix fed to it
	on digital pins 2 to 9. (physical row order is 7,6,5,4,3,2,9,8)
*/
void matrix_tick(LEDmatrix* m) {
	//Do nothing on falling clock
	if (m->clock == 1) {
		PORTB &= ~(1<<TICKPIN);
		m->clock = 0;
	}
	//Change row outputs on rising clock
	else {
		PORTB |= (1<<TICKPIN);
		m->clock = 1;
		m->row = (m->row + 1) % 8;
		PORTD = ((~m->matrix[m->row]) & 0xFC) | (PORTD & 0x03);
		PORTB = ((~m->matrix[m->row]) & 0x03) | (PORTB & 0xFC);
	}
	
}

int state_tick(State* s, LEDmatrix* m) {
	input_t k = 0;
	input_t p = 0;
	if (s->counter == s->clockdivide) {

		s->counter = 0;
		s->step(s, m, k);
	}
	if (s->end == 1) {
		return 1;
	}
	if (input_check(&k, &p)) {
		
		s->click(s, m, k, p);
		if (s->step == 0 || s->end == 1) {
			return 1;
		}
	}
	s->counter++;
	return 0;
}

void state_free(State* s) {
	free(s);
}
