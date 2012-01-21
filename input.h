#ifndef _LED_INPUT_LIB
#define _LED_INPUT_LIB

#include "stdint.h"

typedef uint_fast16_t input_t;

int input_check(input_t * input, input_t * prev);
unsigned char input_get(void);


#endif
