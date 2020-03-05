#include <iostream>
#include <cstdint>
#include <limits>
void foo(unsigned i) {
  std::cout << "unsigned " << i << "\n";
}

template <typename T>
void foo(const T& t) {
  std::cout << "template " << t << "\n";
}

int negate(int i) {
  std::cout << "minus " << -i << "\n";
  return -i;
}

template <typename T>
typename T::value_type negate(const T& t) {
  std::cout << "template minus " << -t << "\n";
  return -t;
}

int main()
{
  foo(42);
  foo(42.1);
  negate(43);
  return 0;
}
