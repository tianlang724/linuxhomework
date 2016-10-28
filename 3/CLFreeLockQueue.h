#include <iostream>       // std::cout
#include <atomic>         // std::atomic
#include <thread>         // std::thread
#include <vector>         // std::vector
#include <stdlib.h>
#include <stdint.h>

#define DEFULT_SIZE 64 
template<typename T,int arrize=DEFULT_SIZE>
class CLFreeLockQueue
{
    public:
    CLFreeLockQueue(){    m_CurrentReadIndex=0;
    m_CurrentWriteIndex=0;}
    bool PushMessage(T);
    T PopMessage();
    private:
    T m_FreeLockQueue[arrize];
    std::atomic<int> m_CurrentWriteIndex;
    std::atomic<int> m_CurrentReadIndex;
    inline int CountToIndex(int index);
    //std::atomic<int>m_MaxReadCount;
};
/*
template<typename T,int arr>
class test
{
    T a;
};
*/