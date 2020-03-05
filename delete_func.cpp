/*
  Copy Constructor and Assignment Operator are deleted. If anybody
  tries to call the deleted function then it will generate compile time error 

  $g++ -o delete_func delete_func.cpp --std=c++11
*/

#include <iostream>
class User
{
 
	int id;
	std::string name;
public:
	User(int userId, std::string userName) : id(userId), name(userName)
	{}
 
	// Copy Constructor is deleted
	User(const User & obj) = delete;
	// Assignment operator is deleted
	User & operator = (const User & obj) = delete;
    // Deleting a constructor that accepts a double as ID to prevent narrowing conversion
    User(double userId, std::string userName) = delete ;
 
    // Deleting a constructor that accepts a double as ID to prevent invalid type conversion
    User(char userId, std::string userName) = delete ; 

   	// Delete the new function to prevent object creation on heap
	void * operator new (size_t) = delete;

	void display()
	{
		std::cout<<id << " ::: "<<name<<std::endl;
	}
 
};

int main()
{
    User userObj(3, "John");
//  User obj = userObj;
    /*
 error: use of deleted function ‘User::User(const User&)’
     User obj = userObj;
                ^~~~~~~
delete_func.cpp:12:2: note: declared here
  User(const User & obj) = delete;
   */
  
    //User obj4(5.5, "Riti");
    //User obj5('a', "Riti");
    /*
    Some times due to automatic type conversion we can call the functions with wrong parameters too. 
    with delete keyword we can prevent them too by declaring them deleted
delete_func.cpp:49:26: error: use of deleted function ‘User::User(double, std::__cxx11::string)’
     User obj4(5.5, "Riti");
                          ^
delete_func.cpp:24:5: note: declared here
     User(double userId, std::string userName) = delete ;
     ^~~~
delete_func.cpp:50:26: error: use of deleted function ‘User::User(char, std::__cxx11::string)’
     User obj5('a', "Riti");
    */

    // User *ptr = new User(1, "Riti");
    /* Restrict Object creation on Heap by deleting new operator for class */
    return 0;
}
