#include "LEDlib.h"
#include "stdint.h"
#include "stdlib.h"
#include "input.h"
//#include "serial_lib_interrupt.h"


static uint8_t * snake_matrix;
static uint8_t * food_matrix;

static uint8_t head_x = 0;
static uint8_t head_y = 0;
static uint8_t tail_x = 0;
static uint8_t tail_y = 0;

#define MATRIX_SET(matrix, x, y) (matrix[(y)] |= (1 << (x)))

void snake_step(State * s, LEDmatrix* m, const input_t input) {

}

void snake_click(State * s, LEDmatrix* m, const input_t input, const input_t prev) {
	if (input & INPUT_LEFT) {

	}
	else if (input & INPUT_RIGHT) {
	
	}
	if (input & INPUT_UP) {

	}
	else if (input & INPUT_DOWN) {

	}
}

void snake_setup(State * s, LEDmatrix* m) {
	
	//Initialise things
	uint8_t i;
	snake_matrix = (uint8_t * )malloc(sizeof(uint8_t) * 8);
	food_matrix = (uint8_t * )malloc(sizeof(uint8_t) * 8);
	
	for (i = 0; i < 8; i++) {
		snake_matirx[i] = 0;
		food_matrix[i] = 0;
	}
	//Add some snake to start with
	MATRIX_SET(food_matrix, 3, 2);
	MATRIX_SET(food_matrix, 4, 2);
	MATRIX_SET(food_matrix, 5, 2);
	head_x = 5;
	head_y = 2;
	tail_x = 3;
	tail_y = 2;
	
	//Food!
	MATRIX_SET(food_matrix, 4, 4)
	
}
