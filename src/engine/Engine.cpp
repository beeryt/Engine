#include <Engine.h>
#include <thread>

#include <cmath>
#include <algorithm>

using std::chrono::milliseconds;
using std::this_thread::sleep_for;


/** \brief Abstract network handler called once per loop
 */
void Engine::network(uint32_t timeout) {
  sleep_for(milliseconds(timeout));
}


/** \brief Abstract update function called once per timestep
 */
void Engine::update() {}


/** \brief Abstract render function called once per frame
 */
void Engine::render(double) {}


/** \brief Handles fixed-timestep updates with decoupled rendering
 *
 *  Inspired by [Fix Your Timestep](https://gafferongames.com/post/fix_your_timestep/)
 *
 *  \returns False if Engine has shutdown, True otherwise
 */
bool Engine::loop() {
  // handle network until frame available
  network(time.untilNextFrame());

  // run updates for pending frames
  time.update();
  while (time.processFrame()) {
    update();
  }

  // render latest frame with interpolation
  auto alpha = time.alpha();
  if (!std::isnan(alpha)) {
    render(alpha);
  }

  return m_running;
}
