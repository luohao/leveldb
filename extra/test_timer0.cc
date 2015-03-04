#include <iostream>
#include <thread>
#include <chrono>
#include "timer0.h"

int
main()
{
  struct stopwatch* sw = get_stopwatch();

  for (int i = 1; i < 10; i ++) {
    stopwatch_start(sw);
    std::this_thread::sleep_for(std::chrono::milliseconds(i * i));
    stopwatch_stop(sw);
  }

  stopwatch_print(sw);
  stopwatch_clear(sw);

  for (int i = 1; i < 10; i ++) {
    stopwatch_start(sw);
    std::this_thread::sleep_for(std::chrono::milliseconds(i * i));
    stopwatch_stop(sw);
  }

  stopwatch_print(sw);

  return 1;
}
