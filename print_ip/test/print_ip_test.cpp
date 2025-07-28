#include <gtest/gtest.h>
#include <list>
#include <sstream>
#include <vector>

#include "print_ip.hpp"

TEST(print, containter) {
  std::stringstream ss;
  std::vector<char> vec_test{1, 2, 3, 4, 5, 6};

  print_ip::print_ip(vec_test, ss);

  ASSERT_EQ(ss.str(), "1.2.3.4.5.6");

  ss.str("");

  std::list<char> list_test{-1};

  print_ip::print_ip(list_test, ss);

  ASSERT_EQ(ss.str(), "-1");
}

TEST(print, integer) {
  char ch = -1;
  short sh = 0;
  int i = 2130706433;
  long li = 8875824491850138409;

  std::stringstream ss;

  print_ip::print_ip(ch, ss);
  ASSERT_EQ(ss.str(), "255");
  ss.str("");

  print_ip::print_ip(sh, ss);
  ASSERT_EQ(ss.str(), "0.0");
  ss.str("");

  print_ip::print_ip(i, ss);
  ASSERT_EQ(ss.str(), "127.0.0.1");
  ss.str("");

  print_ip::print_ip(li, ss);
  ASSERT_EQ(ss.str(), "123.45.67.89.101.112.131.41");
  ss.str("");
}

TEST(print, string) {
  std::stringstream ss;
  std::string out("192.168.1.142");

  print_ip::print_ip(out, ss);
  ASSERT_EQ(ss.str(), "192.168.1.142");
}

TEST(print, tuple) {
  std::stringstream ss;
  print_ip::print_ip(std::make_tuple(1, 2, 3, 4, 5), ss);

  ASSERT_EQ(ss.str(), "1.2.3.4.5");
}
