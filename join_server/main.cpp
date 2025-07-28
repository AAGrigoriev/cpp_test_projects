#include <iostream>

#include "database.hpp"
#include "network.hpp"
#include "parsing.hpp"

using namespace std;

int main(int argc, char** argv) {
  try {
    if (argc != 2) {
      std::cout << "port is required as argument\n";
      return 1;
    }

    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(),
                                            std::stoi(argv[1]));

    boost::asio::io_context io_context;
    auto ctx = std::make_tuple(parsing::operation{}, std::string{},
                               std::size_t{}, std::string{});

    db::database db;

    nett::server(io_context, endpoint, [&](std::string_view sv) -> std::string {
      tao::pegtl::memory_input<tao::pegtl::tracking_mode::eager> in{sv.data(),
                                                                    ""};
      tao::pegtl::parse<parsing::command, parsing::action>(in, ctx);

      const auto& table_id = std::get<1>(ctx);

      switch (std::get<0>(ctx)) {
        case parsing::operation::INSERT: {
          auto result = db.insert(table_id, std::get<2>(ctx), std::get<3>(ctx));
          return result.code ? result.code.message() : result.string;
        }
        case parsing::operation::TRUNCATE: {
          auto result = db.truncate(table_id);
          return result.code ? result.code.message() : result.string;
        }
        case parsing::operation::INTERSECT: {
          return db.intersect();
        }
        case parsing::operation::SYMDIF: {
          return db.symmetric_difference();
        }
      }

      return "ERR unknown\n";
    });

  } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
