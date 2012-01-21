#ifndef _DODGEGAME
#define _DODGEGAME

void dodgegame_step(State * s, LEDmatrix* m, const input_t input);
void dodgegame_click(State * s, LEDmatrix* m, const input_t input, const input_t prev);
void dodgegame_setup(State * s, LEDmatrix* m) ;

#endif
