#pragma once

#include <condition_variable>
#include <functional>
#include <future>
#include <memory>
#include <mutex>
#include <queue>
#include <stdexcept>
#include <thread>
#include <vector>

namespace utility {

class thread_pool {
 public:
  thread_pool(const thread_pool&) = delete;
  thread_pool& operator=(const thread_pool&) = delete;
  thread_pool(thread_pool&&) = delete;
  thread_pool& operator=(thread_pool&&) = delete;

  static thread_pool& get_instance();

  template <typename F, typename... Args>
  void enqueue(F&& f, Args&&... args);
  // template <class F, class... Args>
  // auto enqueue(F&& f, Args&&... args)
  //     -> std::future<typename std::result_of<F(Args...)>::type>;

 private:
  thread_pool(std::size_t);
  ~thread_pool();

  // need to keep track of threads so we can join them
  std::vector<std::thread> workers;
  // the task queue
  std::queue<std::function<void()>> tasks;

  // synchronization
  std::mutex queue_mutex;
  std::condition_variable condition;
  bool stop;
};

template <class F, class... Args>
void thread_pool::enqueue(F&& f, Args&&... args) {
  {
    std::unique_lock<std::mutex> lock(queue_mutex);

    // don't allow enqueueing after stopping the pool
    auto task = std::bind(std::forward<F>(f), std::forward<Args>(args)...);

    if (stop)
      throw std::runtime_error("enqueue on stopped ThreadPool");

    tasks.emplace(std::move(task));
  }
  condition.notify_one();
}

// // add new work item to the pool
// template <class F, class... Args>
// auto thread_pool::enqueue(F&& f, Args&&... args)
//     -> std::future<typename std::result_of<F(Args...)>::type> {
//   using return_type = typename std::result_of<F(Args...)>::type;

//   auto task = std::make_shared<std::packaged_task<return_type()>>(
//       std::bind(std::forward<F>(f), std::forward<Args>(args)...));

//   std::future<return_type> res = task->get_future();
//   {
//     std::unique_lock<std::mutex> lock(queue_mutex);

//     // don't allow enqueueing after stopping the pool
//     if (stop)
//       throw std::runtime_error("enqueue on stopped ThreadPool");

//     tasks.emplace([task]() { (*task)(); });
//   }
//   condition.notify_one();
//   return res;
// }

}  // namespace utility
