#ifndef _SNAKE
#define _SNAKE

#include "charstack.h"
#include "LEDlib.h"
#include "stdint.h"
#include "stdlib.h"
#include "input.h"

void snake_step(State * s, LEDmatrix* m, const input_t input);
void snake_click(State * s, LEDmatrix* m, const input_t input, const input_t prev);
void snake_setup(State * s, LEDmatrix* m) ;



#endif
