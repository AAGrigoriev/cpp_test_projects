#pragma once

#include <iostream>
#include <memory>
#include <thread>

#include "reader.hpp"
#include "worker.hpp"


namespace async {

class cout_writer final : public worker,
                          public std::enable_shared_from_this<cout_writer> {
public:
  static std::shared_ptr<cout_writer> create(const std::string& name, std::size_t start_worker_number, reader& reader, std::ostream& stream = std::cout);

  void process(std::size_t worker_number) override;

private:
  cout_writer(const std::string& worker_name, std::size_t start_worker_number, std::ostream& stream);

private:
  std::ostream& stream_;     ///< Ссылка на глобальный поток std::cout;
  std::mutex    cout_mutex_; ///< mutex для вывода в cout.
};

} // namespace asycn