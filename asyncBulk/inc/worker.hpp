#pragma once

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>

#include "command.hpp"
#include "observer.hpp"


namespace async {
  
class worker : public i_observer<command> {
public:
  virtual void update(const command& command);
  
  virtual void process(std::size_t worker_number) = 0;
  void         create_process();
  
  virtual      ~worker();

protected:
  worker(const std::string& name, std::size_t start_worker_number);

protected:
  std::queue<command>      command_;
  std::mutex               que_mutex_;
  std::condition_variable  cv_;
  std::atomic<bool>        done_;
  std::string              worker_name_;
  std::vector<std::thread> threads_;    ///< Вектор потоков для работы с функцией process(). 

private:
  std::size_t              worker_number_;
};

} // namespace async