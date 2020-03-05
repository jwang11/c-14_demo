#include <iostream>
#include <tuple>
 
template <typename T1, typename T2, typename... Args>
struct type_list
{
   template <std::size_t N>
   using type = typename std::tuple_element<N, std::tuple<T1, T2, Args...>>::type;
   template <std::size_t N>
   using Event = typename std::add_const<type<N>>::type;
   static constexpr int size = sizeof...(Args) + 2;
};

template <std::size_t N>
using mtypes = type_list<int, char, bool, int, char>::type<N>;

template<class... T> struct mp_plus_impl;

template<class... T> using mp_plus = typename mp_plus_impl<T...>::type;

template<> struct mp_plus_impl<>
{
    using type = std::integral_constant<int, 0>;
};

template<class T1, class... T> struct mp_plus_impl<T1, T...>
{
//    static constexpr auto _v = T1::value + mp_plus<T...>::value;
    static constexpr auto _v = !T1::value + mp_plus<T...>::value;

    using type = std::integral_constant<
        typename std::remove_const<decltype(_v)>::type, _v>;
};

template<class L, class V> struct mp_count_impl;

template<template<class...> class L, class... T, class V>
    struct mp_count_impl<L<T...>, V>
{
    using type = mp_plus<std::is_same<T, V>...>;
};

template<class L, class V> using mp_count = typename mp_count_impl<L, V>::type;

typedef mp_count<std::tuple<int, float, int, int>, int> RTCOUNT;
int main()
{
   std::cout << std::boolalpha;
   mtypes<2> x = true;
//   type_list<int, char, bool, int, char>::type<2> x = true;
   type_list<int, char, bool, int, char>::type<0> y = 100;
   type_list<int, char, bool, int, char>::Event<1> z = 'c';
   std::cout << x << '\n';
   std::cout << y << '\n';
   std::cout << z << '\n';
   std::cout << type_list<int, char, bool>::size << std::endl;
   std::cout << mp_count<std::tuple<int, float, float, int, int>, int>::value << '\n';
}
