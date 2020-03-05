#include <iostream>

struct Foo {
    template < typename T,
               typename std::enable_if < !std::is_integral<T>::value, int >::type = 2>
    void f(const T& value)
    {
        std::cout << "Not int: " << value << std::endl;
    }

    template<typename T,
             typename std::enable_if<std::is_integral<T>::value, int>::type = 3>
    void f(const T& value)
    {
        std::cout << "Int: " << value << std::endl;
    }
};

int main()
{
    Foo foo;
    foo.f(1);
    foo.f(1.1);
    foo.f("abc");

    // Output:
    // Int
    // Not int
}
