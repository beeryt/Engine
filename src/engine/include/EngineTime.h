#pragma once

#include <chrono>

class EngineTime {
  public:
    using clock = std::chrono::high_resolution_clock;

    EngineTime();
    template <class A, class B, class C>
      EngineTime(A timestep, B min, C max) :
        timestep(timestep), min(min), max(max) {}

    typename clock::time_point update();
    uint32_t untilNextFrame();
    bool processFrame();
    double alpha();

    typename clock::duration timestep;
    typename clock::duration min;
    typename clock::duration max;

  private:
    typename clock::time_point frame;
    typename clock::time_point render;
    typename clock::duration accumulator;
};
