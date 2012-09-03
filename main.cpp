#include <iostream>
#include "GameObject.h"
#include "geometry.h"

using namespace std;

const double EPS = 0.001;

/** Настройки логики **/

const int 
WIDTH = 640,
	  HEIGHT = 480;

const double 
MAX_ANGLE = PI / 8, // в радианах
		  MIN_ANGLE = -PI / 8,
		  dangle = PI/32; // по модулю

const int
PATH_LEN = 50, // точек
		 PATH_MOD = 10; // итераций на точку пути

const int
INIT_ITER_LEN = 20,
			  ITER_DLEN = 1;

/**! Настройки логики !**/

SDL_Surface *screen = NULL;
void initialize() {
	SDL_Init( SDL_INIT_EVERYTHING );
	screen = SDL_SetVideoMode( WIDTH, HEIGHT, 32, SDL_SWSURFACE );
}

void finalize() {
	SDL_FreeSurface(screen);
	SDL_Quit();
}

int main( int argc, char* args[]) {
	initialize();
	VisualGameObject test("./pic/png/submarine.png");
	test.setCenter(PointI(43, 27));
	test.move_to(PointI(100, 100));
	test.plot(screen);
	for (int i = 0; i < 100; ++i) {
		SDL_FillRect(screen, NULL, 0);
		test.plot(screen);
		if (i % 5 || !i)
			test.scale(1.2);
		else
			test.reset_scale();
		SDL_Delay(100);
	}
	test.plot(screen);
	finalize();
	return 0;    
}
