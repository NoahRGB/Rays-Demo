#pragma once

#include <vector>

#include "SDL3/SDL.h"

#include "vec2.h"

struct circle {
  circle();
  circle(vec2 pos, float radius);

  vec2 pos;
  float radius;

  void draw(SDL_Renderer* renderer);
  std::vector<vec2> getCirclePoints();
};