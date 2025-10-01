#include "circle.h"

#include "math.h"

circle::circle() {
  pos = vec2(0.0f, 0.0f);
  radius = 0.0f;
}

circle::circle(vec2 pos, float radius) {
  this->pos = pos;
  this->radius = radius;
}

void circle::draw(SDL_Renderer* renderer) {
  for (int i = (pos.x - radius); i < (pos.x + radius); i++) {
    for (int j = (pos.y - radius); j < (pos.y + radius); j++) {
      int distance = dist(vec2(i, j), pos);
      if (distance < radius) {
        SDL_RenderPoint(renderer, i, j);
      }
    }
  }
}

std::vector<vec2> circle::getCirclePoints() {
  std::vector<vec2> points;
  for (int i = (pos.x - radius); i < (pos.x + radius); i++) {
    for (int j = (pos.y - radius); j < (pos.y + radius); j++) {
      float distance = dist(vec2(i, j), pos);
      float diff = abs(distance - radius);
      if (diff < 1.0f) {
        points.push_back(vec2(i, j));
      }
    }
  }
  return points;
}