#include "command_parser.hpp"

#include <exception>
#include <iostream>

#include <boost/program_options.hpp>

namespace command_parser {

parser_output parse(int argc, char* argv[]) {
  namespace po = boost::program_options;
  po::options_description opt_description("Server options");
  opt_description.add_options()("help", "print message")(
      "port", po::value<unsigned short>()->required(), "Port")(
      "bulk", po::value<std::size_t>()->required(), "bulk_size");

  po::positional_options_description pos_description;
  pos_description.add("port", 1);
  pos_description.add("bulk", 1);

  po::variables_map var_map;

  try {
    auto parsed = po::command_line_parser(argc, argv)
                      .options(opt_description)
                      .positional(pos_description)
                      .run();

    po::store(parsed, var_map);

    if (var_map.contains("help")) {
      std::cout << opt_description << "\n";
      throw std::exception{};
    }

    po::notify(var_map);

  } catch (const po::error& error) {
    throw std::logic_error("error while parsing command argument");
  }

  const auto bulk_size = var_map["bulk"].as<std::size_t>();
  if (!bulk_size) {
    throw std::logic_error("bulk size must be at least 1");
  }

  const auto port = var_map["port"].as<unsigned short>();

  return {boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port),
          bulk_size};
}

}  // namespace command_parser
