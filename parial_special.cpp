// enable_if example: two ways of using enable_if
#include <iostream>
#include <type_traits>
#include <string>

// the partial specialization of A is enabled via a template parameter
template<class T, class Enable = void>
class A {}; // primary template
 
template<class T>
class A<T, typename std::enable_if<std::is_floating_point<T>::value>::type> {
}; // specialization for floating point types

// 1. the return type (bool) is only valid if T is an integral type:
template <class T>
typename std::enable_if<std::is_integral<T>::value,bool>::type
  is_odd (T i) {return bool(i%2);}

// 2. the second template argument is only valid if T is an integral type:
// Second template argument is only used to enforce T's type, therefore it
// doesn't have a name and it is not used.
template < class T,
           class = typename std::enable_if<std::is_integral<T>::value>::type>
bool is_even (T i) {return !bool(i%2);}
 
int main()
{
    A<int> a1; // OK, matches the primary template
    A<double> a2; // OK, matches the partial specialization

    short int i = 1;    // code does not compile if type of i is not integral

    std::cout << std::boolalpha;
    std::cout << "i is odd: " << is_odd(i) << std::endl;
    std::cout << "i is even: " << is_even(i) << std::endl;

    return 0;
}
