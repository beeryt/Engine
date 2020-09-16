#include <Platform.h>

#ifndef SCREEN_WIDTH
#define SCREEN_WIDTH 680
#endif
#ifndef SCREEN_HEIGHT
#define SCREEN_HEIGHT 480
#endif

Platform::Platform(const char* title) : Platform(
    title,
    glm::ivec2{SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED},
    glm::ivec2{SCREEN_WIDTH, SCREEN_HEIGHT},
    SDL_WINDOW_SHOWN) {}

Platform::Platform(const char* title, glm::ivec2 pos, glm::ivec2 size, SDL_WindowFlags flags) {
  // initialize video subsystem
  if (!(SDL_WasInit(0) & SDL_INIT_VIDEO)) {
    SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Video was not initialized");
    exit(1);
  }

  // create SDL2 window
  m_window = SDL_CreateWindow(title,
      pos.x, pos.y,
      size.x, size.y,
      SDL_WINDOW_OPENGL | flags);
  if (m_window == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Could not create window: %s", SDL_GetError());
    exit(1);
  }

  // create OpenGL context associated with SDL2 window
  m_context = SDL_GL_CreateContext(m_window);
  if (m_context == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Could not create OpenGL context: %s", SDL_GetError());
    exit(1);
  }

  // load OpenGL functions
  if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
    SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Could not load OpenGL functions: TODO");
    exit(1);
  }

  SDL_Log("OpenGL %d.%d", GLVersion.major, GLVersion.minor);
}

Platform::~Platform() {
  SDL_GL_DeleteContext(m_context);
  SDL_DestroyWindow(m_window);
}
