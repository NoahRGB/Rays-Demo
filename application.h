#pragma once

#include <string>
#include <vector>

#include "SDL3/SDL.h"

#include "vec2.h"
#include "circle.h"

class Application {
public:
  Application(std::string name, int width, int height);
  ~Application();

  void run();

private:
  SDL_Window* window;
  SDL_Renderer* renderer;

  int width, height;
  bool done;
  int mouseX, mouseY;

  void tick();
  void handleInput();
  void render();

  bool oldRayCircleIntersect(vec2 pos, int radius, vec2 origin, vec2 dir, float& t);

  circle mouseCircle;
  std::vector<circle> obstacles;

};