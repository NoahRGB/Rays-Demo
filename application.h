#pragma once

#include <string>
#include <vector>

#include "SDL3/SDL.h"

#include "vec2.h"

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

  void drawCircle(vec2 pos, int radius);
  std::vector<vec2> Application::getCirclePoints(vec2 pos, int radius);
  bool Application::rayCircleIntersect(vec2 pos, int radius, vec2 origin, vec2 dir, float& t);
};