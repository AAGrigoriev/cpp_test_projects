#pragma once

#include <boost/asio.hpp>
#include <cstddef>

namespace command_parser {

struct parser_output {
  boost::asio::ip::tcp::endpoint endpoint;
  std::size_t bulk_size;
};

parser_output parse(int argc, char* argv[]);

}  // namespace command_parser
