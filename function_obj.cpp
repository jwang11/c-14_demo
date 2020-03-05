/*
A Function Object / Functor is a kind of Callback with State.

In a Programmer’s terminology,
Object of a class which has overloaded operator() is called Function Object
or Functor i.e. a class with overloaded operator() function is as follows,


#include <iostream>
class MyFunctor
{
public:
    int operator()(int a , int b)
    {
        return a+b;
    }

};

Now lets create a function object and call them,

MyFunctor funObj;
std::cout<<funObj(2,3)<<std::endl;

Functors can be called just like normal functions i.e.

MyFunctor funObj;
funObj(2,3); //equal to funObj.operator ()(2,3);

  $g++ -o function_obj function_obj.cpp --std=c++11
*/

#include <iostream>
 
class Encryptor {
    bool m_isIncremental;
    int m_count;
public:
    Encryptor() {
        m_isIncremental = 0;
        m_count = 1;
    }
    Encryptor(bool isInc, int count) {
        m_isIncremental = isInc;
        m_count = count;
    }
    std::string operator()(std::string data) {
        for (int i = 0; i < data.size(); i++)
            if ((data[i] >= 'a' && data[i] <= 'z')
                    || (data[i] >= 'A' && data[i] <= 'Z'))
                if (m_isIncremental)
                    data[i] = data[i] + m_count;
                else
                    data[i] = data[i] - m_count;
        return data;
    }
 
};
 
std::string buildCompleteMessage(std::string rawData,
        Encryptor encyptorFuncObj) {
    // Add some header and footer to data to make it complete message
    rawData = "[HEADER]" + rawData + "[FooTER]";
 
    // Call the callBack provided i.e. function pointer to encrypt the
    rawData = encyptorFuncObj(rawData);
 
    return rawData;
}
 
int main() {
    std::string msg = buildCompleteMessage("SampleString", Encryptor(true, 1));
    std::cout << msg << std::endl;
 
    msg = buildCompleteMessage("SampleString", Encryptor(true, 2));
    std::cout << msg << std::endl;
 
    msg = buildCompleteMessage("SampleString", Encryptor(false, 1));
    std::cout << msg << std::endl;
 
    return 0;
}
