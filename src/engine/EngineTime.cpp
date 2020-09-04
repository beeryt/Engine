#include <EngineTime.h>

#include <algorithm>
#include <cmath>

/** \brief Returns the time until next frame in milliseconds
 * 
 *  \returns Time until next frame in milliseconds
 */
uint32_t EngineTime::untilNextFrame() {
  using std::clamp;
  using std::round;

  update();

  auto timeout = round<std::chrono::milliseconds>(timestep - accumulator);
  return clamp(timeout, timeout.zero(), timeout.max()).count();
}

/** \brief Updates the accumulator and marks the start of frame
 *
 *  \returns The time_point used to update the accumulator
 */
typename EngineTime::clock::time_point EngineTime::update() {
  using std::clamp;
  auto time = clock::now();
  accumulator += time - frame;
  accumulator = clamp(accumulator, accumulator.zero(), max);
  frame = time;
  return time;
}

/** \brief Processes a single timestep frame from the accumulator
 *
 *  \returns True if a frame was processed, false otherwise
 */
bool EngineTime::processFrame() {
  if (accumulator >= timestep) {
    accumulator -= timestep;
    return true;
  } else return false;
}

/** \brief Determines the alpha between the previous frame and now
 *
 *  \returns A double between 0 and 1 inclusive
 */
double EngineTime::alpha() {
  using std::chrono::duration_cast;
  using std::chrono::duration;
  auto time = update();
  auto elapsed = time - render;
  if (elapsed >= min) {
    render = time;
    return duration_cast<duration<double>>(accumulator) / timestep;
  } else return NAN;
}

EngineTime::EngineTime() : EngineTime(
    std::chrono::milliseconds(16),
    std::chrono::milliseconds(10),
    std::chrono::milliseconds(100)) {}
