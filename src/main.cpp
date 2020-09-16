#include <Engine.h>
#include <Platform.h>
#include <stdio.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

class Game : public Engine {
  protected:
    Platform &m_platform;
  public:
    Game(Platform &p) : m_platform(p) {}
    void input() {
      SDL_Event e;
      SDL_PollEvent(&e);
      switch (e.type) {
        case SDL_QUIT:
          SDL_Log("Program quit after %i ticks", e.quit.timestamp);
          m_running = false;
          break;
      }
    }

    void render(double) {
      static int i = 0;
      i += 2;
      glClearColor(((float)(i % 256))/255.0,0,0,1);
      glClear(GL_COLOR_BUFFER_BIT);
      SDL_GL_SwapWindow(m_platform.m_window);
    }
};

int main() {
  SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
    exit(1);
  }

  Platform p("SDL2 Window",
      {SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED},
      {SCREEN_WIDTH, SCREEN_HEIGHT},
      SDL_WINDOW_SHOWN);

  Game g(p);
  while (g.loop());

  SDL_Quit();
}
