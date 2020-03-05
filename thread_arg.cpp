/*
  Demo passing arguments to thread
  * Be careful to pass arguments to threads in pointer to heap
  Because it might be possible that some thread deletes that memory before new thread tries to access it.

  void newThreadCallback(int * p)
  {
    std::cout<<"Inside Thread :  "" : p = "<<p<<std::endl;
    std::chrono::milliseconds dura( 1000 );
    std::this_thread::sleep_for( dura );
    *p = 19;
  }
  void startNewThread()
  {
    int * p = new int();
    *p = 10;
    std::cout<<"Inside Main Thread :  "" : *p = "<<*p<<std::endl;
    std::thread t(newThreadCallback,p);
    t.detach();
    delete p;
    p = NULL;
  }
  int main()
  {
    startNewThread();
    std::chrono::milliseconds dura( 2000 );
    std::this_thread::sleep_for( dura );
    return 0;
  }

  * Be careful to pass by local stack
    it might be possible that local variable in Thread 1 goes out of scope
    but Thread 2 is still trying to access it through it’s address.

  void newThreadCallback(int * p)
  {
    std::cout<<"Inside Thread :  "" : p = "<<p<<std::endl;
    std::chrono::milliseconds dura( 1000 );
    std::this_thread::sleep_for( dura );
    *p = 19;
  }
  void startNewThread()
  {
    int i = 10;
    std::cout<<"Inside Main Thread :  "" : i = "<<i<<std::endl;
    std::thread t(newThreadCallback,&i);
    t.detach();
    std::cout<<"Inside Main Thread :  "" : i = "<<i<<std::endl;
  }
  int main()
  {
    startNewThread();
    std::chrono::milliseconds dura( 2000 );
    std::this_thread::sleep_for( dura );
    return 0;
  }
  * Pass by value or reference
  $g++ -o thread_arg thread_arg.cpp --std=c++11 -lpthread
*/

#include <iostream>
#include <string>
#include <thread>
void threadCallback(int x, std::string str)
{
    std::cout<<"Passed Number = "<<x<<std::endl;
    std::cout<<"Passed String = "<<str<<std::endl;
}

void threadCallback_ref(int const & x)
{
    int & y = const_cast<int &>(x);
    y++;
    std::cout<<"Inside Thread x = "<<x<<std::endl;
}

class DummyClass {
public:
    DummyClass()
    {}
    DummyClass(const DummyClass & obj)
    {}
    void sampleMemberFunction(int x)
    {
        std::cout<<"Inside sampleMemberFunction "<<x<<std::endl;
    }
};

int main()  
{
    int x = 10;
    std::string str = "Sample String";
    /* pass argument by value */
    std::thread threadObj(threadCallback, x, str);
    threadObj.join();

    /* pass by reference no outside update */
    std::cout<<"In Main Thread : Before Thread Start x = "<<x<<std::endl;
    std::thread threadObj2(threadCallback_ref, x);
    threadObj2.join();
    std::cout<<"In Main Thread : After Thread Joins x = "<<x<<std::endl;

    /* pass reference with outside update */
    std::cout<<"In Main Thread : Before Thread Start x = "<<x<<std::endl;
    std::thread threadObj3(threadCallback_ref,std::ref(x));
    threadObj3.join();
    std::cout<<"In Main Thread : After Thread Start x = "<<x<<std::endl;

    /* assign pointer to member function of a class */
    DummyClass dummyObj;
    std::cout<<"In Main Thread : Before Thread Start x = "<<x<<std::endl;
    std::thread threadObj4(&DummyClass::sampleMemberFunction,&dummyObj, x);
    threadObj4.join();
    std::cout<<"In Main Thread : After Thread Start x = "<<x<<std::endl;
    return 0;
}
