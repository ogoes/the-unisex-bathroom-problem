/**
 * bathroom.hpp
 * 
 * Bathroom Monitor Definition
 * 
 * @author Otávio Goes
 * @since 2020-10-05
 */

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
  std::atomic<long> _males_w, _females_w; // male and female counters

  std::map<utils::SEX, std::atomic<long>*> _waiters; // define a waiting counter based on sex
  std::map<utils::SEX, std::atomic<long>*> _opposites; // define opsite counter based on sex

 public:
  Bathroom();
  void get_in(utils::SEX); // get in bathroom
  void get_out(utils::SEX); // get out of bethroom
};

};  // namespace monitor

#endif