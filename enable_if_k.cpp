#include <iostream>

template<typename T, typename Enable = void>
void dummy(T t)
{
  std::cout << "Generic: " << t << std::endl;
}


template<typename T, typename std::enable_if<std::is_integral<T>::value, int>::type>
void dummy(T t)
{
  std::cout << "Integral: " << t << std::endl;
}


template<typename T, typename std::enable_if<std::is_floating_point<T>::value, int>::type>
void dummy(T t)
{
  std::cout << "Floating point: " << t << std::endl;
}

int main() {
  dummy(5); // Print "Generic: 5"
  dummy(5.); // Print "Generic: 5"
}
