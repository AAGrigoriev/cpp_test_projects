#pragma once

#include "observer.hpp"
#include "simpleCommand.hpp"

#include <iostream>
#include <memory>

namespace Reader {
class Reader : public ISubject<Command> {
public:
 Reader(std::size_t sizeBlock, std::istream& stream = std::cin);
 void run();
 virtual void attach(const std::shared_ptr<IObserver<Command>>& u_ptr) override;
 virtual void detach(const std::shared_ptr<IObserver<Command>>& u_ptr) override;
 void         beforeNotify();
private:
 std::istream& readStream;
 Command       command;
 int32_t       deep;
 std::size_t   sizeBlock;
};
} // namespace Reader
