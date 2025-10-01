#include "ray.h"

#include "math.h"

#include <iostream>

ray::ray(vec2 origin, vec2 dir) {
  this->origin = origin;
  this->dir = dir;
}

bool ray::rayCircleIntersect(const circle& circle, float& t) {
  float a = 1.0;
  float b = dot(dir * 2.0f, origin - circle.pos);
  float c = size(origin - circle.pos) * size(origin - circle.pos) - circle.radius * circle.radius;

  float discriminant = b * b - 4 * a * c;

  if (discriminant < 0) {
    return false;
  } 
  else {
    float t1 = (-b + sqrt(discriminant)) / 2 * a;
    float t2 = (-b - sqrt(discriminant)) / 2 * a;

    if (t1 < 0 && t2 < 0) {
      return false;
    }
    
    if (t1 < 0 && t2 > 0) {
      t = t2;
    } else if (t2 < 0 && t1 > 0) {
      t = t1;
    } else {
      t = std::min(t1, t2);
    }
    return true;
  }
}