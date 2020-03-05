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
}
