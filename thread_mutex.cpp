/*
  Demo use mutex in race condition
  $g++ -o thread_mutex thread_mutex.cpp --std=c++11 -lpthread
*/

#include<iostream>
#include<thread>
#include<vector>
#include<mutex>
 
class Wallet
{
	int mMoney;
	std::mutex mutex;
public:
	Wallet() :mMoney(0){}
    int getMoney()   { 	return mMoney; }
    void addMoney(int money)
    {
		mutex.lock();
    	for(int i = 0; i < money; ++i)
		{
			mMoney++;
		}
		mutex.unlock();
    }
};

int testMultithreadedWallet()
{
    Wallet walletObject;
    std::vector<std::thread> threads;
    for(int i = 0; i < 5; ++i){
        threads.push_back(std::thread(&Wallet::addMoney, &walletObject, 1000));
    }
 
    for(int i = 0; i < threads.size() ; i++)
    {
        threads.at(i).join();
    }
    return walletObject.getMoney();
}
 
int main()
{
 
	int val = 0;
	for(int k = 0; k < 1000; k++)
	{
		if((val = testMultithreadedWallet()) != 5000)
		{
			std::cout << "Error at count = "<<k<<"  Money in Wallet = "<<val << std::endl;
			//break;
		}
	}
	return 0;
}
