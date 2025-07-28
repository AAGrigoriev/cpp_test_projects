#include "file_writer.hpp"

#include <fstream>
#include <utility>


namespace async {

std::shared_ptr<file_writer> file_writer::create(const std::string& name, std::size_t start_worker_number, reader& reader) {
  auto shared_writer = std::shared_ptr<file_writer>(new file_writer(name, start_worker_number));
  reader.subscribe(shared_writer);
  return shared_writer;
}


file_writer::file_writer(const std::string& worker_name, std::size_t start_worker_number)
  : worker(worker_name, start_worker_number) {
  create_process();
}


void file_writer::process(std::size_t worker_number) {
  while(!done_) {
    std::unique_lock lk(que_mutex_);
    cv_.wait(lk, [&] { return !command_.empty() || done_; });
    if (command_.empty()) {
      return;
    }
    auto log_command = std::move(command_.front());
    command_.pop();
    lk.unlock();

    std::ofstream log(worker_name_ + std::to_string(worker_number), std::ios::app);
    log << log_command << std::endl;
    log.close();
  }
}
} // namespace async