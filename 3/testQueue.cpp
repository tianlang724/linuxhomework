#include "CLFreeLockQueue.h"
#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <vector>     
#include <atomic>
#include <pthread.h>
#include <unistd.h>
using namespace std;
void *pushMessage(void * arg)
{
    CLFreeLockQueue<int> *myqueue=(CLFreeLockQueue<int>* )arg;

    for(int i=0;i<25;i++)
    {
        if(myqueue->PushMessage(i))
            cout<<" push "<<i<<endl;
        else 
        cout<<" queue full"<<endl;
    }
}
void *popMessage(void * arg)
{
    CLFreeLockQueue<int> *myqueue=(CLFreeLockQueue<int>* )arg;
    for(int i=0;i<25;i++)
    cout<<" pop "<<myqueue->PopMessage()<<endl;
}
int main()
{
    CLFreeLockQueue<int> myqueue;
    std::vector<std::thread> threads,threads2;
    std::cout << "spawning 10 threads that count to 1 million...\n";
    for (int i = 1; i <= 10; ++i) threads.push_back(std::thread(pushMessage,(void*)&myqueue));
    for (int i = 1; i <= 10; ++i) threads2.push_back(std::thread(popMessage,(void*)&myqueue));
    for (auto& th : threads) th.join();
    for (auto& th : threads2) th.join();  

    return 0;
}
