#include "async.hpp"

using namespace std;

int main() {
  auto context = async::connect();
  auto context_2 = async::connect();
  async::receive(context, "1", 1);
  async::receive(context, "123\n2123\n3333\n4333\n5333\n6333\n", 6);
  async::receive(context_2, "abc\nacc\nabc\nabc\nabc\n", 5);
  async::disconnect(context);
  async::disconnect(context_2);

  return 0;
}
