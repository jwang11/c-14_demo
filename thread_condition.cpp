/*
  Demo condition variable 
Wait()

It makes the current thread to block until the condition variable get signaled or a spurious wake up happens.

It atomically releases the attached mutex, blocks the current thread, and adds it to the list of threads waiting on the current condition variable object. The thread will be unblocked when some thread calls notify_one() or notify_all() on same condition variable object. It may also be unblocked spuriously, therefore after every unblocking it needs to check condition again.

A callback is passed as an parameter to this function, which will be called to check if it is a spurious call or actually condition is met.

When threads get unlocked,

wait() function reacquires the mutex lock and checks that actually condition is met or not. If condition is not met then again it atomically releases the attached mutex, blocks the current thread, and adds it to the list of threads waiting on the current condition variable object.

notify_one()

If any threads are waiting on same conditional variable object then  notify_one unblocks one of the waiting threads.

notify_all()

If any threads are waiting on same conditional variable object then  notify_all unblocks all of the waiting threads.

  $g++ -o thread_condition thread_condition.cpp --std=c++11 -lpthread
*/

#include <iostream>
#include <thread>
#include <functional>
#include <mutex>
#include <condition_variable>

using namespace std::placeholders;
class Application
{
  std::mutex m_mutex;
  std::condition_variable m_condVar;
  bool m_bDataLoaded;

public:
  Application()
  {
    m_bDataLoaded = false;
  }

  void loadData()
  {
   // Make This Thread sleep for 1 Second
   std::this_thread::sleep_for(std::chrono::milliseconds(1000));
   std::cout<<"Loading Data from XML"<<std::endl;
   // Lock The Data structure
   std::lock_guard<std::mutex> guard(m_mutex);
   // Set the flag to true, means data is loaded
   m_bDataLoaded = true;
   // Notify the condition variable
   m_condVar.notify_one();
  }

  bool isDataLoaded()
  {
    return m_bDataLoaded;
  }

  void mainTask()
  {
    std::cout<<"Do Some Handshaking"<<std::endl;
    // Acquire the lock
    std::unique_lock<std::mutex> mlock(m_mutex);
    // Start waiting for the Condition Variable to get signaled
    // Wait() will internally release the lock and make the thread to block
    // As soon as condition variable get signaled, resume the thread and
    // again acquire the lock. Then check if condition is met or not
    // If condition is met then continue else again go in wait.
    m_condVar.wait(mlock, std::bind(&Application::isDataLoaded, this));
    std::cout<<"Do Processing On loaded Data"<<std::endl;
  }
};

int main()
{
   Application app;
   std::thread thread_1(&Application::mainTask, &app);
   std::thread thread_2(&Application::loadData, &app);
   thread_2.join();
   thread_1.join();
   return 0;
}
