#include <Engine.h>

int main() {
  Engine e;
  for (int i = 0; i < 5; ++i) {
    e.loop();
  }
}
