#include "charstack.h"

/*
Return a pointer to a new stack.
	@size is the maximum number of elements.
*/
LIFOuint8 * stack_create(unsigned int size) {
	LIFO * stack;
	stack = (LIFOuint8*)malloc(sizeof(LIFOuint8));
	stack->elements = malloc(size * sizeof(uint8_t));
	stack->pos = 0;
	stack->size = size;
	return stack;
}

/*
Pushes the given uint8_t on to the stack. 
Return the new index.
*/
int stack_push(LIFOuint8 * stack, uint8_t item) {
	if (stack->pos == stack->size) {
		//Fail
		return -1;
	}
	stack->elements[stack->pos] = item;
	return stack->pos++;
}

uint8_t stack_pop(LIFOuint8 * stack) {
	if (stack->pos == 0) {
		//Fail
		return 0;
	}
	uint8_t item = stack->elements[stack->pos - 1];
	stack->pos  = stack->pos - 1;
	return item;
}


/* Return pointer to top element */
uint8_t stack_peek(LIFOuint8 * stack) {
	if (stack->pos == 0) {
		//Fail
		return 0;
	}
	uint8_t = stack->elements[stack->pos - 1];
	return item;
}

/* Return pointer to top element */
uint8_t stack_look(LIFOuint8 * stack, int back) {
	if (stack->pos - back == 0) {
		//Fail
		return 0;
	}
	uint8_t = stack->elements[stack->pos - 1 - back];
	return item;
}

uint8_t stack_free(LIFOuint8 * stack) {
	free(stack->elements);
	free(stack);
}

//I don't think we can call this a stack any more...
//Shift all elements down, return first element.
uint8_t stack_shift(LIFOuint8 * stack) {
	if (stack->pos == 0) {
		//Fail
		return 0;
	}
	uint8_t item = stack->elements[0];
	unsigned int i;
	for (i = 1; i < stack->pos; i++) {
		stack->elements[i - 1] = stack->elements[i];
	}
	stack->pos = stack->pos - 1;
	return item;
}
