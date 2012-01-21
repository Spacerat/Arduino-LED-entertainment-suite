#ifndef _LED_MATRIX_LIB
#define _LED_MATRIX_LIB

#include "input.h"
#include "stdint.h"

struct _LEDmatrix;
struct _State;

//void somefunction(LEDmatrix * m) {};
typedef void (*state_func)(struct _State*, struct _LEDmatrix*);

//void somefunction(LEDmatrix * m, const unsigned char input) {};
typedef void (*state_func_input)(struct _State*, struct _LEDmatrix*, const input_t);
typedef void (*state_func_input_two)(struct _State*, struct _LEDmatrix*, const input_t, const input_t);

typedef struct _LEDmatrix{
	uint8_t row;
	uint_fast8_t clock;
	uint8_t matrix[8];

	
} LEDmatrix;

typedef struct _State {
	state_func_input step;
	state_func_input_two click;
	
	unsigned int clockdivide;
	unsigned int counter;
	
	int end;
	LEDmatrix m;
} State;


void matrix_setup(LEDmatrix*);

State * state_create(state_func setup, LEDmatrix* m);
void matrix_tick(LEDmatrix* m);
int state_tick(State* s, LEDmatrix* m);
void state_free(State * s);
void matrix_clear(LEDmatrix *m);
#endif
