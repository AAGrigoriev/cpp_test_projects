#include <concepts>
#include <list>
#include <string>
#include <vector>

namespace print_ip {

template <typename T>
concept not_string = !std::same_as<T, std::string>;

template <typename T>
concept has_begin_end = requires(T cont) {
  cont.begin();
  cont.end();
};

template <typename T>
concept not_string_and_has_begin_end = not_string<T> && has_begin_end<T>;

template <typename T, template <typename...> class TT>
constexpr bool is_instantiation_of_v = false;

template <template <typename...> class TT, typename... TS>
constexpr bool is_instantiation_of_v<TT<TS...>, TT> = true;

template <class C, template <typename...> class TT>
concept instantiation_of = is_instantiation_of_v<C, TT>;

template <typename T>
concept is_vector_or_list =
    instantiation_of<T, std::vector> || instantiation_of<T, std::list>;

}  // namespace print_ip
