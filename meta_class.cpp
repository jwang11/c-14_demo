#include <iostream>
#include <type_traits>
 
struct foo
{
    void m() { std::cout << "Non-cv\n"; }
    void m() const { std::cout << "Const\n"; }
};
 
template <class T>
void call_m()
{
    T().m();
}
 
int main()
{
    call_m<foo>();
    call_m<std::add_const<foo>::type>();
    const int i = 5;
    int& j = std::remove_const<int>::type(i);
}
