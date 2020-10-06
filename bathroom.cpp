/**
 * bathroom.cpp
 * 
 * Implements Bathroom methods
 * 
 * @author Otávio Goes
 * @since 2020-10-05
 */

#include "./bathroom.hpp"

namespace bathroom {


/**
 * Bathroom constructor
 * 
 * initialize counter with 0 and define waiters and oposites base on utils::SEX enum
 * 
 */
Bathroom::Bathroom() : _males_w(0), _females_w(0) {
  _waiters[utils::SEX::MALE] = &_males_w;
  _waiters[utils::SEX::FEMALE] = &_females_w;

  _opposites[utils::SEX::MALE] = &_females_w;
  _opposites[utils::SEX::FEMALE] = &_males_w;
}

/**
 * Verify condition and wait if necessary, otherwise increment the specific counter (based on sex)
 *
 * @param sex perseon defined sex
 */
void Bathroom::get_in(utils::SEX sex) {

  std::unique_lock<std::mutex> lock(*this); // creates critic zone

  // wait if there's oposite sex in bathroom or max number is reached
  while (_waiters[sex]->load() >= BATHROOM_MAX || _opposites[sex]->load() > 0)
    this->wait(lock);
  lock.unlock(); // exit critic zone


  // if not wait, increment counter
  long load = _waiters[sex]->load();
  while (!_waiters[sex]->compare_exchange_strong(load, load + 1))
    ;
}


/**
 * Decrement counter (based on sex) and notify threads that are waiting
 * 
 * @param sex perseon defined sex
 */
void Bathroom::get_out(utils::SEX sex) {

  // decrement counter
  long load = _waiters[sex]->load();
  while (!_waiters[sex]->compare_exchange_strong(load, load - 1))
    ;

  // notify waiting folks
  this->notify_all();
}
};  // namespace bathroom