#include <stdint.h>
#include <stdlib.h>

typedef struct {
	unsigned int size; //Maximum size of array
	unsigned int pos; //Current position of top
	uint8_t * elements; //Array of uint8_ts
} LIFOuint8;

LIFOuint8 * stack_create(unsigned int size);
int stack_push(LIFOuint8 * stack, uint8_t item);
uint8_t stack_pop(LIFOuint8 * stack);
uint8_t stack_peek(LIFOuint8 * stack);
uint8_t stack_look(LIFOuint8 * stack, int back);
uint8_t stack_shift(LIFOuint8);
