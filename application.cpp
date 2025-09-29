#include "application.h"

#include <iostream>

Application::Application(std::string name, int width, int height) {
  SDL_Init(SDL_INIT_VIDEO);
  this->width = width;
  this->height = height;

  SDL_CreateWindowAndRenderer(name.c_str(), width, height, 0, &window, &renderer);
  SDL_HideCursor();

  done = false;
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

void Application::drawCircle(vec2 pos, int radius) {
  for (int i = (pos.x - radius); i < (pos.x + radius); i++) {
    for (int j = (pos.y - radius); j < (pos.y + radius); j++) {
      int distance = dist(vec2(i, j), pos);
      if (distance < radius) {
        SDL_RenderPoint(renderer, i, j);
      }
    }
  }
}

std::vector<vec2> Application::getCirclePoints(vec2 pos, int radius) {
  std::vector<vec2> points;
  for (int i = (pos.x - radius); i < (pos.x + radius); i++) {
    for (int j = (pos.y - radius); j < (pos.y + radius); j++) {
      int distance = dist(vec2(i, j), pos);
      if (distance == radius) {
        points.push_back(vec2(i, j));
      }
    }
  }
  return points;
}

void Application::render() {
  SDL_SetRenderDrawColor(renderer, 54, 54, 54, 255);
  SDL_RenderClear(renderer);

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);


  vec2 circleOrigin = vec2(mouseX, mouseY);
  drawCircle(circleOrigin, 50);

  std::vector<vec2> circlePoints = getCirclePoints(circleOrigin, 50);



  for (vec2 point : circlePoints) {
    vec2 direction = normalise(vec2(point.x - circleOrigin.x, point.y - circleOrigin.y));
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 100);
    SDL_RenderLine(renderer, point.x, point.y, (point.x + direction.x * 200), (point.y + direction.y * 200));

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 100);
    SDL_RenderLine(renderer, point.x, point.y, circleOrigin.x, circleOrigin.y);

  }


  SDL_RenderPresent(renderer);
}

