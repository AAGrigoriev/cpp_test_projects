#pragma once

#include <string>
#include <tuple>

#include <tao/pegtl.hpp>

namespace parsing {

enum class operation { INSERT, TRUNCATE, INTERSECT, SYMDIF };

using namespace tao::pegtl;

struct table : pad<ascii::upper, ascii::blank, ascii::blank> {};

struct id : pad<plus<ascii::digit>, ascii::blank, ascii::blank> {};

struct field : pad<plus<ascii::alnum>, ascii::blank, ascii::blank> {};

struct insert : seq<pad<ascii::string<'I', 'N', 'S', 'E', 'R', 'T'>,
                        ascii::blank,
                        ascii::blank>,
                    table,
                    id,
                    field> {};

struct truncate : seq<pad<ascii::string<'T', 'R', 'U', 'N', 'C', 'A', 'T', 'E'>,
                          ascii::blank,
                          ascii::blank>,
                      table> {};

struct intersect
    : pad<ascii::string<'I', 'N', 'T', 'E', 'R', 'S', 'E', 'C', 'T'>,
          ascii::blank,
          ascii::blank> {};

struct sym_dif : pad<string<'S',
                            'Y',
                            'M',
                            'M',
                            'E',
                            'T',
                            'R',
                            'I',
                            'C',
                            '_',
                            'D',
                            'I',
                            'F',
                            'F',
                            'E',
                            'R',
                            'E',
                            'N',
                            'C',
                            'E'>,
                     ascii::blank,
                     ascii::blank> {};

struct command : sor<insert, truncate, intersect, sym_dif> {};

// Rule definition

template <typename Rule>
struct action : nothing<Rule> {};

template <>
struct action<insert> {
  template <typename T, typename C>
  static void apply(const T&, C& ctx) {
    std::get<0>(ctx) = operation::INSERT;
  }
};

template <>
struct action<truncate> {
  template <typename T, typename C>
  static void apply(const T&, C& ctx) {
    std::get<0>(ctx) = operation::TRUNCATE;
  }
};

template <>
struct action<intersect> {
  template <typename T, typename C>
  static void apply(const T&, C& ctx) {
    std::get<0>(ctx) = operation::INTERSECT;
  }
};

template <>
struct action<sym_dif> {
  template <typename T, typename C>
  static void apply(const T&, C& ctx) {
    std::get<0>(ctx) = operation::SYMDIF;
  }
};

template <>
struct action<table> {
  template <typename T, typename C>
  static void apply(const T& in, C& ctx) {
    std::get<1>(ctx) = in.string();
  }
};

template <>
struct action<id> {
  template <typename T, typename C>
  static void apply(const T& in, C& ctx) {
    std::get<2>(ctx) = std::stoi(in.string());
  }
};

template <>
struct action<field> {
  template <typename T, typename C>
  static void apply(const T& in, C& ctx) {
    std::get<3>(ctx) = in.string();
  }
};

}  // namespace parsing
