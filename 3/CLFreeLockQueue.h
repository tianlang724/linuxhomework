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
    CLFreeLockQueue(){    m_CurrentReadIndex=0;m_CurrentWriteIndex=0;}
    bool PushMessage(T element);
    T PopMessage();
    private:
    T m_FreeLockQueue[arrize];
    std::atomic<int> m_CurrentWriteIndex;
    std::atomic<int> m_CurrentReadIndex;
    inline int CountToIndex(int index);
    //std::atomic<int>m_MaxReadCount;
};
template<typename T,int arrize>
bool
CLFreeLockQueue<T,arrize>::PushMessage(T element)
{
    int CurrentWriteIndex;
    int NewWriteIndex;
    do
    {
        CurrentWriteIndex = m_CurrentWriteIndex;
        NewWriteIndex=CountToIndex(CurrentWriteIndex+1);
        if(NewWriteIndex==m_CurrentReadIndex)
            continue;
        if(m_CurrentWriteIndex.compare_exchange_weak(CurrentWriteIndex,NewWriteIndex))
            break;
    }while(1);
    m_FreeLockQueue[CurrentWriteIndex] = element;
    return true;
}
template<typename T,int arrize>
inline int
CLFreeLockQueue<T,arrize>::CountToIndex(int index)
{
    return index%arrize;
}

template<typename T,int arrize>
T
CLFreeLockQueue<T,arrize>::PopMessage()
{
    int CurrentReadIndex;
    int NewReadIndex;
    do
    {
        CurrentReadIndex = m_CurrentReadIndex;  
        NewReadIndex=CountToIndex(CurrentReadIndex+1);
        if(CurrentReadIndex==m_CurrentWriteIndex)
            continue ;
        if(m_CurrentReadIndex.compare_exchange_weak(CurrentReadIndex,NewReadIndex))
            break;
    }while(1);
    return m_FreeLockQueue[CurrentReadIndex];
} 
