#include <avr/io.h>
#include <util/delay.h>
#include <stdarg.h>
#include <stdlib.h>
#include <avr/interrupt.h>

#include "LEDlib.h"
#include "input.h"
//#include "serial_lib_interrupt.h"

#include "animation1.h"
#include "animation2.h"
#include "dodgegame.h"

volatile unsigned int tick = 0;

ISR(TIMER0_OVF_vect)
{
	tick = 1;
}

// Set up the menu
int menu_y = 0;
int menu_x = 0;

// Define menu functionality
void menu_step(State * s, LEDmatrix* m, const input_t input) {
}

void menu_click(State * s, LEDmatrix* m, const input_t input, const input_t prev) {
	m->matrix[menu_y] = 0;
	if (input & 4) { //Up
		menu_y = (menu_y == 7 ? 0 : menu_y + 1);
	}
	if (input & 8) { //Down
		menu_y = (menu_y == 0 ? 7 : menu_y - 1);
	}
	if (input & 2) {
		switch (menu_y) {
			case 1:
				state_free(s);
				s = state_create(&animation1_setup, m);
				return;
			case 2:
				state_free(s);
				s = state_create(&animation2_setup, m);
				return;
			case 3:
				state_free(s);
				s = state_create(&dodgegame_setup, m);
				return;
		}
	}
	m->matrix[menu_y] = (1 << menu_x);
}

//Reset menu
void menu_setup(State * s, LEDmatrix* m) {
	menu_x = 0;
	menu_y = 0;
	m->matrix[menu_y] = (1 << menu_x);
	s->step = &menu_step;
	s->click = &menu_click;
	
}

//Entry - Set up everything, begin main loop
int main (void)
{
	//serial_init();

	// Set up the clock interrupt
	TCCR0B = (1<<CS01)|(1<<CS00); //Timer clock = system/64
	TIMSK0 = 1<<TOIE0; //Enable Timer0
	
	sei();
	
	// Set up the matrix and main loop
	LEDmatrix matrix;
	LEDmatrix * m = &matrix;
	matrix_setup(m);
	State * s = state_create(&menu_setup, m);
	
	while (1) {
		if (tick) {
			matrix_tick(m);
			int r = state_tick(s, m);
			if (r) {
				free(s);
				s = state_create(&menu_setup, m);
			}
			tick = 0;
		}
	}

	return 0;
}
