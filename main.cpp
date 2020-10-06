/**
 * main.cpp
 *
 * The Unisex Bathroom
 *
 * @author Otávio Goes
 * @since 2020-10-05
 */

#include <chrono> // std::chrono
#include <ctime> // time
#include <iostream> // std::cout, std::endl
#include <thread> // std::thread
#include <vector> // std::vector

#include "./bathroom.hpp" // bathroom::Bathroom
#include "./utils.hpp" // utils::SEX

/**
 * This funcion defines each thread behavior:
 * * Randomly choose a sex
 * * Get in
 * * Wait a random time (milliseconds) (0, 2000]
 * * Get out
 * 
 * @param thread_id defines the thread sequential number
 * @param bathroom the unisex bathroom controller
 * 
 */
void person_task(long thread_id, bathroom::Bathroom* bathroom) {
  utils::SEX sex = utils::SEX(rand() % 2);

  bathroom->get_in(sex);
  std::cout << "Thread [" << thread_id << "] GET IN [";
  std::cout << (sex == utils::SEX::MALE ? "MALE" : "FEMALE") << ']'
            << std::endl;

  std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 2000));

  bathroom->get_out(sex);
  std::cout << "Thread [" << thread_id << "] GET OUT [";
  std::cout << (sex == utils::SEX::MALE ? "MALE" : "FEMALE") << ']'
            << std::endl;
}

int main() {
  srand(time(nullptr)); // to use random values

  std::vector<std::thread> threads; // threads vector

  auto bathroom = new bathroom::Bathroom(); // unisex bathroom controller

  long thread_number = std::thread::hardware_concurrency() * 2;

  for (long i = 0; i < thread_number; ++i) {
    threads.push_back(std::thread(&person_task, i, bathroom)); // create threads passing id (i) and bathroom controller (bathroom)
  }

  for (auto& thread : threads) thread.join(); // wait for all threads

  return 0; // exit successfully
}