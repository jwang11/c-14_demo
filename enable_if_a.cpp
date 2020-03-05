#include <iostream>
#include <type_traits>

struct Foo {
    template <class T,
               typename = std::enable_if<!std::is_integral<T>::value>>
    void f(const T& value)
    {
        std::cout << "Not int: " << value << std::endl;
    }
/*
    template<class T,
             typename = std::enable_if_t<std::is_integral<T>::value>>
    void f(const T& value)
    {
        std::cout << "Int: " << value << std::endl;
    }
*/
};

int main()
{
    Foo foo;
 //   foo.f(1);
    foo.f(1.1);
    foo.f("abc");

    // Output:
    // Int
    // Not int
}
