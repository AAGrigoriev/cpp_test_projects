#pragma once 

#include "observer.hpp"
#include "simpleCommand.hpp"

namespace Reader {
class FileWriter : public IObserver<Command> {
public:
    FileWriter() = default;
    void update(const Command &command) override;
};
} // namespace Reader
