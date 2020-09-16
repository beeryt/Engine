#pragma once

#include <chrono>
#include <EngineTime.h>

class Engine {
  protected:
    bool m_running;

  public:
    Engine() : Engine(EngineTime()) {};
    Engine(EngineTime time) : time(time) {}

    bool loop();
    virtual void input();
    virtual void network(uint32_t);
    virtual void update();
    virtual void render(double);

  private:
    EngineTime time;
};
