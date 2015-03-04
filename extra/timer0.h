#ifndef _EXTRA_TIMER0_H_
#define _EXTRA_TIMER0_H_
/*
 * global timers for sqlite3 benchmark...
 */
#include <stdio.h>
#include <sys/time.h>

static uint64_t
cur_usec()
{
  struct timeval tv;
  gettimeofday(&tv, 0);
  return ((uint64_t)tv.tv_sec) * 1000000 + tv.tv_usec;
}

struct stopwatch {
 double sum_;
 double max_;
 int count_;

 uint64_t start_;
};

// use static variable in a function to mimic the singleton...
struct stopwatch*
get_stopwatch()
{
  static struct stopwatch sw;
  return &sw;
}

void
stopwatch_start(struct stopwatch* sw)
{
  sw->start_ = cur_usec();
}

void
stopwatch_stop(struct stopwatch* sw)
{
  uint64_t t0 = sw->start_;
  uint64_t t1 = cur_usec();
  double elaps = (double)(t1 - t0);
  if (elaps > sw->max_) {
    sw->max_ = elaps;
  }
  sw->sum_ += elaps;
  sw->count_ ++;
  sw->start_ = 0;
}

void
stopwatch_clear(struct stopwatch* sw)
{
  sw->sum_ = 0;
  sw->count_ = 0;
  sw->max_ = 0;
  sw->start_ = 0;
}

void
stopwatch_print(struct stopwatch* sw)
{
  printf("Average time: %f, Max time: %f\n", (sw->sum_ / sw->count_), sw->max_);
}


#endif
