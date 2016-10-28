#include <iostream>       // std::cout
#include <atomic>         // std::atomic
#include <thread>         // std::thread
#include <vector>         // std::vector
#include <stdlib.h>
#include <stdint.h>

#define DEFULT_SIZE 64 
template<typename T,uint32_t arrize=DEFULT_SIZE>
class CLFreeLockQueue
{
    public:
    CLFreeLockQueue();
    bool PushMessage(T);
    T PopMessage();
    private:
    T m_FreeLockQueue[arrize];
    std::atomic<int> m_CurrentWriteIndex;
    std::atomic<int> m_CurrentReadIndex;
    inline int CountToIndex(int index);
    //std::atomic<int>m_MaxReadCount;
};
