#ifndef _LED_INPUT_LIB
#define _LED_INPUT_LIB

#define INPUT_LEFT  1
#define INPUT_RIGHT 2
#define INPUT_DOWN  4
#define INPUT_UP    8

#include "stdint.h"

typedef uint_fast16_t input_t;

int input_check(input_t * input, input_t * prev);
unsigned char input_get(void);


#endif
