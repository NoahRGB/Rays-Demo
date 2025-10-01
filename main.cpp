#include <string>
#include <iostream>

#include "application.h"

#include "SDL3/SDL.h"
#include "SDL3/SDL_main.h"

// cmake --build build --target run

const int WIDTH = 1500;
const int HEIGHT = 1000;

int main(int argv, char** args) {

	Application app("Learning", WIDTH, HEIGHT);
	app.run();

	return 0;
}