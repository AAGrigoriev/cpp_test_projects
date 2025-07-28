#pragma once

#include <memory>
#include <thread>

#include "reader.hpp"
#include "worker.hpp"


namespace async {

class file_writer final : public worker,
                          public std::enable_shared_from_this<file_writer> {
public:
  static std::shared_ptr<file_writer> create(const std::string& name, std::size_t start_worker_number, reader& reader);

  void process(std::size_t worker_number) override;

private:
  // todo 1: private constructor.
  // https://stackoverflow.com/questions/8147027/how-do-i-call-stdmake-shared-on-a-class-with-only-protected-or-private-const
  file_writer(const std::string& worker_name, std::size_t start_worker_number);
};
} // namespace async