#pragma once

#include <list>
#include <memory>

#include "command.hpp"


namespace async {

template <typename T> class i_observer {
public:
  virtual void update(const T& command) = 0;
  ~i_observer() = default;
};

template <typename T> class i_observable {
public:
  void subscribe(const std::shared_ptr<i_observer<T>>& obs) {
    list_.push_back(obs);
  }

  void notify(const T& data) {
    auto start = list_.begin();
    while (start != list_.end()) {
      auto s_ptr = start->lock();
      if (s_ptr) {
        s_ptr->update(data);
        ++start;
      } else {
        start = list_.erase(start);
      }
    }
  }

private:
  std::list<std::weak_ptr<i_observer<T>>> list_;
};

} // namespace async