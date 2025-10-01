#pragma once

struct vec2 {
    vec2();
    vec2(float x, float y);
    float x, y;

    vec2 operator-(const vec2& v) const {
        return vec2(x - v.x, y - v.y);
    }

    vec2 operator*(float num) const {
        return vec2(x * num, y * num);
    }
};

float dist(const vec2& v1, const vec2& v2);
vec2 norm(const vec2& v);
float dot(const vec2& v1, const vec2& v2);
float size(const vec2& v);