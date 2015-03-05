#ifndef _EXTRA_TIMER_H_
#define _EXTRA_TIMER_H_

#include <iostream>
#include <sstream>
#include <string>

#include <sys/time.h>

class timer {
private:
  timer(const timer &t);

public:
  timer()
  {
    lap();
  }

  uint64_t
  lap()
  {
    uint64_t t0 = start;
    uint64_t t1 = cur_usec();
    start = t1;
    return t1 - t0;
  }

private:
  static uint64_t
  cur_usec()
  {
    struct timeval tv;
    gettimeofday(&tv, 0);
    return ((uint64_t)tv.tv_sec) * 1000000 + tv.tv_usec;
  }

  uint64_t start;
};

class scoped_timer {
private:
  timer t;
  std::string region;

public:
  scoped_timer(const std::string &region) : region(region)
  {}

  ~scoped_timer()
  {
    double x = t.lap() / 1000.0; // ms
    std::cerr << "timed region '" << region << "' took " << x << " ms" << std::endl;
  }
};

class stopwatch {
 private:
  // private ctor to enfore singleton
  stopwatch() : sum_(0), count_(0), t_(NULL){ ; }

  double sum_;
  double max_;
  int count_;

  timer* t_;

 public:
  ~stopwatch() {
    if (t_) {
      delete t_;
    }
  }

  inline void
  start()
  {
    t_ = new timer;
  }
  inline void
  stop()
  {
    double elaps = t_->lap();
    
    if (max_ < elaps) {
      max_ = elaps;
    }
    sum_ += elaps;
    count_ ++;

    delete t_;
    t_ = NULL;
  }

  inline void
  clear()
  {
    sum_ = 0;
    max_ = 0;
    count_ = 0;
    t_ = NULL;
  }

  static stopwatch&
  get()
  {
    static stopwatch sw;
    return sw;
  }

  inline void
  print()
  {
    std::cerr << "Average Time '" << sum_ / count_ << " us, Max " << max_ << " us" << std::endl;
  }
};

// global variable

#endif 
