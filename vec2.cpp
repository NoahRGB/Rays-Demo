#include "vec2.h"

#include <math.h>

vec2::vec2(float x, float y) {
    this->x = x;
    this->y = y;
}

float dist(vec2& v1, vec2& v2) {
    return sqrt((v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y));
}

vec2 normalise(vec2& v) {
    float len = size(v);
    return vec2(v.x / len, v.y / len);
}

float dot(vec2& v1, vec2& v2) {
    return v1.x * v2.x + v1.y * v2.y;
}

float size(vec2& v) {
    return sqrt(v.x * v.x + v.y * v.y);
}