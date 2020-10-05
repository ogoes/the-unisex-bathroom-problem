#include <chrono>
#include <ctime>
#include <iostream>
#include <thread>
#include <vector>

#include "./bathroom.hpp"
#include "./utils.hpp"

class Person {
 private:
  long _id;

 public:
  Person(long thread_id) : _id(thread_id){};

  void operator()(bathroom::Bathroom* bathroom) {
    utils::SEX sex = utils::SEX(rand() % 2);

    bathroom->get_in(sex);
    std::cout << "Thread [" << _id << "] GET IN, SEX [";
    std::cout << (sex == utils::SEX::MALE ? "MALE" : "FEMALE") << ']'
              << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 2000));


    std::cout << "Thread [" << _id << "] GET OUT, SEX [";
    std::cout << (sex == utils::SEX::MALE ? "MALE" : "FEMALE") << ']'
              << std::endl;
    bathroom->get_out(sex);

  };
};

int main() {
  srand(time(nullptr));

  std::vector<std::thread> threads;

  auto bathroom = new bathroom::Bathroom();

  long thread_number = 9l;

  for (long i = 0; i < thread_number; ++i) {
    threads.push_back(std::thread(Person(i), bathroom));
  }

  for (auto& thread : threads) thread.join();

  return 0;
}