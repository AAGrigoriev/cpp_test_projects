#pragma once 

#include "observer.hpp"
#include "simpleCommand.hpp"

#include <iostream>

namespace Reader {
class ConsoleWriter : public IObserver<Command> {
public:
    ConsoleWriter();
    ConsoleWriter(std::ostream &stream);
    void update(const Command &command) override;

private:
    std::ostream& console;
};

} // namespace Reader
