#include "CLFreeLockQueue.h"
#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <vector>     
#include <atomic>
#include <pthread.h>
#include <unistd.h>
using namespace std;
/*
template<typename T,int arrize>
void pushMessage(CLFreeLockQueue<T,arrize> &queue,int i)
{
    queue.PushMessage(i);
    cout<<"push "<<i<<endl;
}
template<typename T,int arrize>
void  popMessage(CLFreeLockQueue<T,arrize>& queue)
{
    cout<<"pop"<<queue.PopMessage()<<endl;
}
*/
int threadid=0;
void *pushMessage(void * arg)
{
    CLFreeLockQueue<int,15> *myqueue=(CLFreeLockQueue<int,15>* )arg;
    for(int i=0;i<25;i++)
    {
        if(myqueue->PushMessage(i))
            cout<<threadid<<" push "<<i<<endl;
        else 
        cout<<" queue full"<<endl;
    }
}
void *popMessage(void * arg)
{
    CLFreeLockQueue<int,15> *myqueue=(CLFreeLockQueue<int,15>* )arg;
    for(int i=0;i<25;i++)
    cout<<" pop "<<myqueue->PopMessage()<<endl;
}
int main()
{
    CLFreeLockQueue<int,15> myqueue;
    /****单生产者单消费者测试***/
    
   /* pthread_t id1,id2;
    pthread_create (&id1, NULL, pushMessage, (void*)&myqueue);
    pthread_create (&id2, NULL, popMessage, (void*)&myqueue);
    pthread_join(id2,NULL);
    pthread_join(id1,NULL);   */

    std::vector<std::thread> threads,threads2;
    std::cout << "spawning 10 threads that count to 1 million...\n";
    for (int i = 1; i <= 10; ++i) threads.push_back(std::thread(pushMessage,(void*)&myqueue));
    for (int i = 1; i <= 10; ++i) threads2.push_back(std::thread(popMessage,(void*)&myqueue));
    for (auto& th : threads) th.join();
    for (auto& th : threads2) th.join();  

    return 0;
}