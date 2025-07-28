#include "reader.hpp"
#include <iostream>

Reader::Reader::Reader(std::size_t sizeBlock, std::istream& stream)
    : deep(0), readStream(stream), sizeBlock(sizeBlock) {}

void Reader::Reader::run() {
  std::string line;
  while (std::getline(readStream, line)) {
    if (line == "{") {
      if (deep == 0)
        beforeNotify();
      ++deep;
    } else if (line == "}") {
      if (deep != 0)
        --deep;
      if (!deep)
        beforeNotify();
    } else {
      command.put_command(std::move(line));

      if (!deep && command.getCommand().size() >= sizeBlock)
        beforeNotify();
    }
  }
}

void Reader::Reader::attach(const std::shared_ptr<IObserver<Command>>& u_ptr) {
  F_list.push_front(u_ptr);
}

void Reader::Reader::detach(const std::shared_ptr<IObserver<Command>>& u_ptr) {
  F_list.remove_if([&u_ptr](const auto& weak_ptr) {
    if (auto ptr = weak_ptr.lock()) {
      return ptr.get() == u_ptr.get();
    }
    return false;
  });
}

void Reader::Reader::beforeNotify() {
  if (command.getCommand().size() > 0)
    notify(command);

  command.clearCommand();
}
