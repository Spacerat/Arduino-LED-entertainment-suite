
#include "snake.h"
//#include "serial_lib_interrupt.h"

#define MATRIX_SET(matrix, x, y) (matrix[(y)] |= (1 << (x)))
#define MATRIX_UNSET(matrix, x, y) (matrix[(y)] &= ~(1 << (x)))
#define MATRIX_CHECK(matrix, y, y) (matrix[(y)] & (1 << (x)))

#define SNAKECOORD(x, y) ((x << 4) | (y))
#define SNAKE_X(coord) ((coord & 0xF0) >> 4)
#define SNAKE_Y(coord) ((coord & 0x0F))

//Le snake!
typedef struct _snake {	
	uint8_t heading = 0;
	LIFOuint8 * parts;
} Snake;

//Set up a new snake struct. Snake starts at tailx/taily and extends horizontally by length units
Snake * create_snake(uint8_t tailx, uint8_t taily, uint8_t length) {
	Snake *s;
	uint8_t i;
	s = (Snake*)malloc(sizeof(Snake));

	s->parts = stack_create(8*8);
	
	for (i = 0; i < length; i++) {
		stack_push(s->parts, SNAKECOORD(tailx + i, taily));
	}
	
	return s;
}

//Matrix for positions of food
static uint8_t * food_matrix;

//List of pointers to snakes (for now, just one snake).
#define SNAKE_COUNT 1
static Snake * snakes[SNAKE_COUNT];

void snake_step(State * state, LEDmatrix* m, const input_t input) {
	uint8_t n;
	uint8_t k;
	unsigned int i;
	Snake *s;
	uint8_t next_x;
	uint8_t next_y;
	uint8_t next_tail_x;
	uint8_t next_tail_y;
	
	unsigned int grow = 0;
	for (n = 0; n < SNAKE_COUNT; n++) {
		s = snakes[n];
		next_x = SNAKE_X(stack_peek(s->parts));
		next_y = SNAKE_Y(stack_peek(s->parts));
		
		switch (s->heading) {
			case INPUT_LEFT:
				next_x -= 1;
				break;
			case INPUT_RIGHT:
				next_x += 1;
				break;
			case INPUT_UP:
				next_y -= 1;
				break;
			case INPUT_DOWN:
				next_y += 1;
				break;
		}
		
		//Check for foood, remove tail if there is none!
		if (MATRIX_CHECK(food_matrix, next_x, next_y)) {
			MATRIX_UNSET(food_matrix, next_x, next_y);
			//TODO: make sure we don't spawn food on snake
			MATRIX_SET(food_matrix, rand() % 8, rand() % 8);
		}
		else {
			stack_shift(snake->parts);
		}
		
		stack_push(snake->parts, SNAKECOORD(next_x, next_y);
		
		//Check for collision with any snake
		
		for (k = 0; k < SNAKE_COUNT; k++) {
			for(i = 0; i < snake->parts->pos; i++) {
				if (next_x == SNAKE_X(snake->parts[i]) && next_y == SNAKE_Y(snake->parts[i])) {
					state->end = 1;
					snakegame_free();
				}
			}
		}
	}
}

//Free all allocated memory
static void snakegame_free() {
	unsigned int i;
	for (i = 0; i < SNAKE_COUNT; i++) {
		stack_free(snakes[i]->parts);
		free(snakes[i]);
	}
	free(snakes);
	free(food_matrix);
}

void snake_click(State * s, LEDmatrix* m, const input_t input, const input_t prev) {
	if (input & INPUT_LEFT) {
		snakes[0]->heading = INPUT_LEFT;
	}
	else if (input & INPUT_RIGHT) {
		snakes[0]->heading = INPUT_RIGHT;
	}
	if (input & INPUT_UP) {
		snakes[0]->heading = INPUT_UP;
	}
	else if (input & INPUT_DOWN) {
		snakes[0]->heading = INPUT_DOWN;
	}
}

void snake_setup(State * s, LEDmatrix* m) {
	
	//Initialise things
	uint8_t i;
	
	food_matrix = (uint8_t * )malloc(sizeof(uint8_t) * 8);
	
	for (i = 0; i < 8; i++) {
		food_matrix[i] = 0;
	}
	//Add some snake to start with
	snakes[0] = create_snake(3, 3, 3);
	
	//Food!
	MATRIX_SET(food_matrix, 4, 4)
	
}
