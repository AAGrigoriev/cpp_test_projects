#include "worker.hpp"

#include <functional>
#include <mutex>


namespace async {

worker::worker(const std::string& worker_name, std::size_t start_worker_number) 
 : worker_name_(worker_name), worker_number_(start_worker_number)
  {}


void worker::create_process() {
  threads_.emplace_back(&worker::process, this, worker_number_++);
}

void worker::update(const command& command) {
  {
    std::lock_guard lc(que_mutex_);
    command_.push(command);
  }
  cv_.notify_one();
}

worker::~worker() {
  done_ = true;
  cv_.notify_all();
  for (auto&& thread : threads_) {
    thread.join();
  }
}
} // namespace async