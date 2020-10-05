#include "./bathroom.hpp"

namespace bathroom {

Bathroom::Bathroom() : _males_w(0), _females_w(0) {
  _waiters[utils::SEX::MALE] = &_males_w;
  _opposites[utils::SEX::MALE] = &_females_w;

  _waiters[utils::SEX::FEMALE] = &_females_w;
  _opposites[utils::SEX::FEMALE] = &_males_w;
}

void Bathroom::get_in(utils::SEX sex) {

  std::unique_lock<std::mutex> lock(*this);
  while (_waiters[sex]->load() >= BATHROOM_MAX ||
         _opposites[sex]->load() > 0)
    this->wait(lock);
  lock.unlock();

  long load = _waiters[sex]->load();
  while (!_waiters[sex]->compare_exchange_strong(load, load + 1))
    ;
}

void Bathroom::get_out(utils::SEX sex) {
  long load = _waiters[sex]->load();
  while (!_waiters[sex]->compare_exchange_strong(load, load - 1))
    ;

  this->notify_all();
}
};  // namespace bathroom