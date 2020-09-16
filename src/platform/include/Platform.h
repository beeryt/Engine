#pragma once
#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

class Platform {
  protected:
  public:
    SDL_Window* m_window = NULL;
    SDL_GLContext m_context = NULL;

    Platform(const char*);
    Platform(const char*, glm::ivec2, glm::ivec2, SDL_WindowFlags);
    ~Platform();
};
