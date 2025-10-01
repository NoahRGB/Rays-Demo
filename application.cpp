#include "application.h"
#include "circle.h"
#include "ray.h"

#include <iostream>
#include "math.h"

Application::Application(std::string name, int width, int height) {
  SDL_Init(SDL_INIT_VIDEO);
  this->width = width;
  this->height = height;

  SDL_CreateWindowAndRenderer(name.c_str(), width, height, 0, &window, &renderer);
  SDL_HideCursor();

  done = false;

  mouseCircle = { vec2(0.0f, 0.0f), 50.0f };
  obstacles.push_back({ vec2(200.0f, 200.0f), 50.0f });
  obstacles.push_back({ vec2(400.0f, 400.0f), 50.0f });
}

Application::~Application() {
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
}

void Application::run() {
  int fps = 0;
  Uint64 lastTime = 0;

  while (!done) {
    Uint64 currentTime = SDL_GetTicks();
    tick();
    fps++;

    if (currentTime > lastTime + 1000) {
      lastTime = currentTime;
      std::string title = "FPS: " + std::to_string(fps);
      SDL_SetWindowTitle(window, title.c_str());
      fps = 0;
    }
  }
}

void Application::tick() {
  handleInput();
  render();
}

void Application::handleInput() {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_EVENT_QUIT) {
      done = true;
    }
    if (e.type == SDL_EVENT_KEY_DOWN) {
      if (e.key.key == SDLK_ESCAPE) {
        done = true;
      }
    }
    if (e.type == SDL_EVENT_MOUSE_MOTION) {
      mouseX = e.motion.x;
      mouseY = e.motion.y;
    }
  }
}

bool Application::oldRayCircleIntersect(vec2 pos, int radius, vec2 origin, vec2 dir, float& t) {
  float a = 1.0;
  float b = dot(dir * 2.0f, origin - pos);
  float c = size(origin - pos) * size(origin - pos) - radius * radius;

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

void Application::render() {
  SDL_SetRenderDrawColor(renderer, 54, 54, 54, 255);
  SDL_RenderClear(renderer);

  mouseCircle.pos.x = mouseX;
  mouseCircle.pos.y = mouseY;

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  mouseCircle.draw(renderer);
  for (circle obstacle : obstacles) {
    obstacle.draw(renderer);
  }
  

  std::vector<vec2> circlePoints = mouseCircle.getCirclePoints();

  for (vec2 point : circlePoints) {
    ray ray(point, norm(vec2(point - mouseCircle.pos)));

    bool hitFound = false;
    float bestT = 999;

    for (circle obstacle : obstacles) {
      float t;
      bool hit = ray.rayCircleIntersect(obstacle, t);
      if (hit) {
        hitFound = true;
        if (t < bestT) bestT = t;
      }
    }
    
    SDL_SetRenderDrawColor(renderer, 255, 225, 0, 255);
    if (hitFound) {
      SDL_RenderLine(renderer, ray.origin.x, ray.origin.y, (ray.origin.x + ray.dir.x * bestT), (ray.origin.y + ray.dir.y * bestT));
    } else {
      SDL_RenderLine(renderer, ray.origin.x, ray.origin.y, (ray.origin.x + ray.dir.x * 500), (ray.origin.y + ray.dir.y * 500));
    }
  }

  SDL_RenderPresent(renderer);
}

