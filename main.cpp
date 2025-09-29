#include <string>
#include <iostream>

#include "application.h"

#include "SDL3/SDL.h"
#include "SDL3/SDL_main.h"

// cmake --build build --target run

const int WIDTH = 1000;
const int HEIGHT = 500;

int main(int argv, char** args) {

	Application app("Learning", 500, 500);
	app.run();

	return 0;
}