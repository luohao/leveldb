#include <iostream>
#include <atomic>
#include <condition_variable>
#include <thread>
#include <chrono>
#include "timer.h"

int
main()
{
  stopwatch sw;

  for (int i = 1; i < 10; i ++) {
    sw.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(i * i));
    sw.stop();
  }

  sw.print();
  sw.clear();

  for (int i = 1; i < 10; i ++) {
    sw.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(i * i));
    sw.stop();
  }

  sw.print();

  return 1;
}
