#include <iostream>

#include <boost/asio.hpp>

#include "command_parser.hpp"
#include "server.hpp"

using boost::asio::ip::tcp;

int main(int argc, char* argv[]) {
  command_parser::parser_output context;
  try {
    context = command_parser::parse(argc, argv);

    boost::asio::io_context io_context;
    boost::asio::signal_set signals(io_context, SIGINT, SIGTERM);

    network::server server(io_context, context.endpoint, context.bulk_size);

    signals.async_wait([&io_context](const boost::system::error_code& error,
                                     int /*signal_number*/) {
      if (!error) {
        io_context.stop();
      }
    });

    io_context.run();

  } catch (std::exception& ex) {
    std::cerr << ex.what() << std::endl;
    return 1;
  }

  return 0;
}
