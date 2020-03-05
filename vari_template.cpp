/*
Variadic Template is introduced in C++11. Variadic Template allows 
a function to take variable number of arguments of any type.

  $g++ -o vari_template vari_template.cpp --std=c++11
*/

#include <iostream>
 
// Function that accepts no parameter
// It is to break the recursion chain of vardiac template function
void log()
{
}
 
/*
 * Variadic Template Function that accepts variable number
 * of arguments of any type.
 */
template<typename T, typename ... Args>
void log(T first, Args ... args) {
 
	// Print the First Element
	std::cout<<first<<" , ";
 
	// Forward the remaining arguments
	log(args ...);
}
 
 
int main() {
 
	log(2, 3.4, "aaa");
 
	return 0;
}
