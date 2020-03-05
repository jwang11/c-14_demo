/*
How to pass outer scope elements inside lambda functions
Case 1: Using [=]
    [=](int &x) {
        // All outer scope elements has been passed by value
    }
Case 2: Using [&]
    [&](int &x) {
        // All outer scope elements has been passed by reference
    }
  $g++ -o lambda_func lambda_func.cpp --std=c++11
*/

#include <iostream>
#include <algorithm>
 
int main() {
    int arr[] = { 1, 2, 3, 4, 5 };
 
    int mul = 5;
 
    std::for_each(arr, arr + sizeof(arr) / sizeof(int), [&](int x) {
        std::cout<<x<<" ";
        // Can modify the mul inside this lambda function because
        // all outer scope elements has write access here.
            mul = 3;
        });
    std::cout << std::endl;
 
    std::for_each(arr, arr + sizeof(arr) / sizeof(int), [=](int &x) {
        x= x*mul;
        // Can not modify the mul inside this lambda function because
        // all outer scope elements has read only access here.
        // mul = 9;
 
        });
    std::cout << std::endl;
 
    std::for_each(arr, arr + sizeof(arr) / sizeof(int), [](int x) {
 
        // No access to mul inside this lambda function because
        // all outer scope elements are not visible here.
        //std::cout<<mul<<" ";
        });
    std::cout << std::endl;
 
}
