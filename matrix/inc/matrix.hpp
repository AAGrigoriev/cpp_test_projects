#pragma once

#include <tuple>
#include <unordered_map>

#include "hashFunction.hpp"

namespace otus_matrix {
template <typename T,
          T def_v,
          typename = typename std::enable_if<std::is_integral<T>::value>::type>
class matrix {
 private:
  class container_wrapper {
   public:
    using size_type =
        typename std::unordered_map<hash_key, T, hash_functions>::size_type;
    using iterator =
        typename std::unordered_map<hash_key, T, hash_functions>::iterator;

    container_wrapper() = default;
    ~container_wrapper() = default;

    /*!
        @brief Get value using indexes.
    */
    T get(std::size_t row_index, std::size_t col_index) {
      auto search = u_map.find(hash_key(row_index, col_index));
      return search == u_map.end() ? def_v : search->second;
    }

    /*!
        @brief Function assign value to unordered_map
    */
    void assign(std::size_t row_index, std::size_t col_index, T value) {
      if (value != def_v) {
        u_map[hash_key(row_index, col_index)] = value;
      } else {
        u_map.erase(hash_key(row_index, col_index));
      }
    }

    iterator begin() { return u_map.begin(); }

    iterator end() { return u_map.end(); }

    size_type size() { return u_map.size(); }

   private:
    std::unordered_map<hash_key, T, hash_functions> u_map;
  };

  class proxy_column {
   public:
    proxy_column(std::size_t index_row,
                 std::size_t index_col,
                 container_wrapper& container)
        : index_row(index_row), index_col(index_col), container(container) {}

    proxy_column& operator=(T value) {
      container.assign(index_row, index_col, value);
      return *this;
    }

    operator T() { return container.get(index_row, index_col); }

    bool operator==(T other) const {
      return container.get(index_row, index_col) == other;
    }

    bool operator!=(T other) {
      return container.get(index_row, index_col) != other;
    }

    ~proxy_column() = default;

   private:
    std::size_t index_row;
    std::size_t index_col;
    container_wrapper& container;
  };

  class proxy_row {
   public:
    proxy_row(std::size_t index_row, container_wrapper& container)
        : index_row(index_row), container(container) {}

    proxy_column operator[](std::size_t index_column) {
      return proxy_column(index_row, index_column, container);
    }

    ~proxy_row() = default;

   private:
    std::size_t index_row;
    container_wrapper& container;
  };

  class iterator {
   public:
    using value_type = std::tuple<std::size_t, std::size_t, T>;
    using difference_type = std::size_t;
    using reference = value_type&;
    using pointer = value_type*;
    using iterator_category = std::forward_iterator_tag;

    iterator(typename container_wrapper::iterator iter) : iter(iter) {}

    value_type operator*() {
      return std::make_tuple(iter->first.first, iter->first.last, iter->second);
    }

    iterator& operator++() {
      ++iter;
      return *this;
    }

    bool operator==(const iterator& other) { return (iter == other.iter); }

    bool operator!=(const iterator& other) { return !(*this == other); }

   private:
    typename container_wrapper::iterator iter;
  };

 public:
  matrix() = default;
  ~matrix() = default;

  proxy_row operator[](std::size_t index_row) {
    return proxy_row(index_row, container);
  }

  typename container_wrapper::size_type size() { return container.size(); }

  iterator begin() { return iterator(container.begin()); }

  iterator end() { return iterator(container.end()); }

 private:
  container_wrapper container;
};

}  // namespace otus_matrix
