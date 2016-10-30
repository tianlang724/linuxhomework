#include "CLFreeLockQueue.h"
#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <vector>     
using namespace std;
template<typename T,int arrize>
void pushMessage(CLFreeLockQueue<T,arrize> &queue,int i)
{
    queue.PushMessage<T>(i);
    cout<<"push "<<i<<endl;
}
/*
void  popMessage(CLFreeLockQueue<T,arrize>& queue)
{
    cout<<"pop"<<queue.PopMessage()<<endl;
}
*/
int main()
{
    CLFreeLockQueue<int,6> myqueue;
    int i=0;
    pushMessage<int,6>(myqueue,i);
    //std::vector<std::thread> threads,threads2;
    //std::cout << "spawning 10 threads that count to 1 million...\n";
    //for (int i = 1; i <= 10; ++i) threads.push_back(std::thread((pushMessage<int,10>),myqueue,i));
    //for (int i = 1; i <= 10; ++i) threads2.push_back(std::thread(popMessage,myqueue));
   // for (auto& th : threads) th.join();
   // for (auto& th : threads2) th.join();

    return 0;
}