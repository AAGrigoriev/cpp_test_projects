#pragma once

#include <boost/asio.hpp>

namespace network {

namespace asio = boost::asio;

class server {
 public:
  server(asio::io_context& io_context,
         const asio::ip::tcp::endpoint& endpoint,
         std::size_t bulk_size);

 private:
  void do_accept();

 private:
  asio::ip::tcp::acceptor acceptor_;
  std::size_t bulk_size_;
};

}  // namespace network
