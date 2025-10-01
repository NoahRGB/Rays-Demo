
struct vec2 {
    vec2(float x, float y);
    float x, y;

    vec2 operator-(const vec2& v) const {
        return vec2(x - v.x, y - v.y);
    }

    vec2 operator*(float num) {
        x *= num;
        y *= num;
        return *this;
    }
};

float dist(vec2& v1, vec2& v2);
vec2 normalise(vec2& v);
float dot(vec2& v1, vec2& v2);
float size(vec2& v);