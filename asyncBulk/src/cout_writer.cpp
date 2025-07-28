#include "cout_writer.hpp"

#include <thread>
#include <iostream>


namespace async {

std::shared_ptr<cout_writer> cout_writer::create(const std::string& name, std::size_t start_worker_number, reader& reader, std::ostream& stream) {
  /// todo: Лучше использовать make_shared, но нужно геммороится из-за приватного конструктора.
  auto shared_writer = std::shared_ptr<cout_writer>(new cout_writer(name, start_worker_number, stream));
  reader.subscribe(shared_writer);
  return shared_writer;
}


cout_writer::cout_writer(const std::string& worker_name, std::size_t start_worker_number, std::ostream& stream)
    : worker(worker_name, start_worker_number), stream_(stream) {
  create_process();
}


void cout_writer::process(std::size_t worker_number) {
  while (!done_) {
    std::unique_lock lk(que_mutex_);
    cv_.wait(lk, [&] { return !command_.empty() || done_; });
    if (command_.empty()) {
      return;
    }
    auto command_to_execute = std::move(command_.front());
    command_.pop();
    lk.unlock();
    {
      std::lock_guard lock(cout_mutex_);
      stream_ << worker_number << " " << command_to_execute << std::endl;
    }
  }
}
} // namespace async
