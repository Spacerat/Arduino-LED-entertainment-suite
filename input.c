
#include "input.h"
#include <avr/io.h>
#include <stdarg.h>
#include <stdio.h>

static unsigned char disabled = 0;

#define PI0 PINC0
#define PI1 PINC1
#define PI2 PINC2
#define PI3 PINC3
#define PI4 disabled
#define PI5 disabled
#define PI6 disabled
#define PI7 disabled

#define DDRI0 DDRC
#define DDRI1 DDRC
#define DDRI2 DDRC
#define DDRI3 DDRC
#define DDRI4 disabled
#define DDRI5 disabled
#define DDRI6 disabled
#define DDRI7 disabled

#define PINI0 PINC
#define PINI1 PINC
#define PINI2 PINC
#define PINI3 PINC
#define PINI4 disabled
#define PINI5 disabled
#define PINI6 disabled
#define PINI7 disabled

static unsigned char now_input = 0;

unsigned char input_init(void) {
	DDRI0 &= ~(0 << PI0);
	DDRI1 &= ~(0 << PI1);
	DDRI2 &= ~(0 << PI2);
	DDRI3 &= ~(0 << PI3);
	DDRI4 &= ~(0 << PI4);
	DDRI5 &= ~(0 << PI5);
	DDRI6 &= ~(0 << PI6);
	DDRI7 &= ~(0 << PI7);
}

int input_check(input_t * input, input_t * prev) {
	input_t c = (PINI0 & (1 << PI0)) 
	                | (PINI1 & (1 << PI1))
	                | (PINI2 & (1 << PI2))
	                | (PINI3 & (1 << PI3))
	                | (PINI4 & (1 << PI4))
	                | (PINI5 & (1 << PI5))
	                | (PINI6 & (1 << PI6))
	                | (PINI7 & (1 << PI7));
	input_t i = now_input;
	now_input = c;
	*input = c;
	*prev = i;
	return (i != now_input);
}

unsigned char input_get(void) {
	return now_input;
}
