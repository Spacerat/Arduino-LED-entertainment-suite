#ifndef _LED_MATRIX_LIB
#define _LED_MATRIX_LIB


struct _LEDmatrix;
struct _State;

//void somefunction(LEDmatrix * m) {};
typedef void (*state_func)(struct _State*, struct _LEDmatrix*);

//void somefunction(LEDmatrix * m, const unsigned char input) {};
typedef void (*state_func_input)(struct _State*, struct _LEDmatrix*, const unsigned char);
typedef void (*state_func_input_two)(struct _State*, struct _LEDmatrix*, const unsigned char, const unsigned char);

typedef struct _LEDmatrix{
	unsigned char row;
	unsigned char clock;
	unsigned char matrix[8];

	
} LEDmatrix;

typedef struct _State {
	state_func_input step;
	state_func_input_two click;
	
	unsigned int clockdivide;
	unsigned int counter;
	LEDmatrix m;
} State;


void matrix_setup(LEDmatrix*);

State * state_create(state_func setup, LEDmatrix* m);
void matrix_tick(LEDmatrix* m);
int state_tick(State* s, LEDmatrix* m);
void state_free(State * s);
void matrix_clear(LEDmatrix *m);
#endif
