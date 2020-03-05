#include <iostream>
#include <cstdint>
#include <limits>

int main()
{
  std::cout << std::numeric_limits<double>::max() << std::endl;
  std::cout << std::numeric_limits<double>::max() / 1.1 << std::endl;
  std::cout << std::numeric_limits<long double>::max() << std::endl;
  std::cout << std::numeric_limits<uint64_t>::max() << std::endl;
  double max_uint64 = static_cast<double>(std::numeric_limits<uint64_t>::max());
  std::cout << max_uint64 << std::endl;
  std::cout << static_cast<uint64_t>(max_uint64 * 0.99999) << std::endl;
  return 0;
}
