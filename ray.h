#pragma once

#include "vec2.h"
#include "circle.h"

struct ray {
  ray(vec2 origin, vec2 dir);

  vec2 origin;
  vec2 dir;

  
  
  bool rayCircleIntersect(const circle& circle, float& t);
};