#ifndef BATHROOM_HPP
#define BATHROOM_HPP

#include <atomic>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <map>

#include "./utils.hpp"

const static long BATHROOM_MAX = 3;

namespace bathroom {

class Bathroom : protected std::mutex, protected std::condition_variable {
 private:
  std::atomic<long> _males_w, _females_w;

  std::map<utils::SEX, std::atomic<long>*> _waiters;
  std::map<utils::SEX, std::atomic<long>*> _opposites;

 public:
  Bathroom();
  void get_in(utils::SEX);
  void get_out(utils::SEX);
};

};  // namespace monitor

#endif