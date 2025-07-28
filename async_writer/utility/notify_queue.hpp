#pragma once

#include <condition_variable>
#include <mutex>
#include <queue>

namespace async {

template <typename T>
class notifying_queue {
 public:
  notifying_queue() {}
  notifying_queue(const notifying_queue& other) = delete;

  bool try_pop(T& t) {
    std::unique_lock lock(m_mutex);

    m_cv.wait(lock, [this] { return m_queue.size() > 0 || m_stopping; });

    if (m_queue.size() > 0) {
      t = std::move(m_queue.front());
      m_queue.pop();
      return true;
    }

    return false;
  }

  void push(const T& t) {
    {
      std::unique_lock lock(m_mutex);
      m_queue.push(t);
    }
    m_cv.notify_one();
  }

  void notify_stopping() {
    {
      std::unique_lock lock(m_mutex);
      m_stopping = true;
    }

    m_cv.notify_all();
  }

  std::queue<T> get_queue() const {
    std::unique_lock lock(m_mutex);
    return m_queue;
  }

 private:
  std::queue<T> m_queue;
  bool m_stopping = false;
  mutable std::mutex m_mutex;
  std::condition_variable m_cv;
};

}  // namespace async
