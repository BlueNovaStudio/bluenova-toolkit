#pragma once

#include <array>
#include <deque>
#include <list>
#include <map>
#include <set>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace cpp_printer::detail
{
    template <typename T>
    using remove_cvref_t = std::remove_cv_t<std::remove_reference_t<T>>;

    template <typename T>
    struct is_map_like : std::false_type {};

    template <typename Key, typename Value, typename... Args>
    struct is_map_like<std::map<Key, Value, Args...>> : std::true_type {};
    template <typename Key, typename Value, typename... Args>
    struct is_map_like<std::multimap<Key, Value, Args...>> : std::true_type {};
    template <typename Key, typename Value, typename... Args>
    struct is_map_like<std::unordered_map<Key, Value, Args...>> : std::true_type {};
    template <typename Key, typename Value, typename... Args>
    struct is_map_like<std::unordered_multimap<Key, Value, Args...>> : std::true_type {};

    template <typename T>
    inline constexpr bool is_map_like_v = is_map_like<remove_cvref_t<T>>::value;

    template <typename T>
    struct is_set_like : std::false_type {};

    template <typename Key, typename... Args>
    struct is_set_like<std::set<Key, Args...>> : std::true_type {};
    template <typename Key, typename... Args>
    struct is_set_like<std::multiset<Key, Args...>> : std::true_type {};
    template <typename Key, typename... Args>
    struct is_set_like<std::unordered_set<Key, Args...>> : std::true_type {};
    template <typename Key, typename... Args>
    struct is_set_like<std::unordered_multiset<Key, Args...>> : std::true_type {};

    template <typename T>
    inline constexpr bool is_set_like_v = is_set_like<remove_cvref_t<T>>::value;

    template <typename T>
    struct is_unordered : std::false_type {};

    template <typename Key, typename Value, typename... Args>
    struct is_unordered<std::unordered_map<Key, Value, Args...>> : std::true_type {};
    template <typename Key, typename Value, typename... Args>
    struct is_unordered<std::unordered_multimap<Key, Value, Args...>> : std::true_type {};
    template <typename Key, typename... Args>
    struct is_unordered<std::unordered_set<Key, Args...>> : std::true_type {};
    template <typename Key, typename... Args>
    struct is_unordered<std::unordered_multiset<Key, Args...>> : std::true_type {};

    template <typename T>
    inline constexpr bool is_unordered_v = is_unordered<remove_cvref_t<T>>::value;

    template <typename T>
    struct is_ordered_sequence : std::false_type {};

    template <typename Value, typename Allocator>
    struct is_ordered_sequence<std::vector<Value, Allocator>> : std::true_type {};
    template <typename Value, typename Allocator>
    struct is_ordered_sequence<std::deque<Value, Allocator>> : std::true_type {};
    template <typename Value, typename Allocator>
    struct is_ordered_sequence<std::list<Value, Allocator>> : std::true_type {};
    template <typename Value, std::size_t Size>
    struct is_ordered_sequence<std::array<Value, Size>> : std::true_type {};

    template <typename T>
    inline constexpr bool is_ordered_sequence_v = is_ordered_sequence<remove_cvref_t<T>>::value;
}
