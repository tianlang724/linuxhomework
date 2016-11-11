#ifndef CLFREELOCKQUEUE_H
#define CLFREELOCKQUEUE_H
#include <iostream>       // std::cout
#include <atomic>         // std::atomic
#include <thread>         // std::thread
#include <vector>         // std::vector
#include <stdlib.h>
#include <stdint.h>

#define DEFULT_SIZE 30 
template<typename T,int arrize=DEFULT_SIZE>
class CLFreeLockQueue
{
    public:
    CLFreeLockQueue(){    m_CurrentReadIndex=0;m_CurrentWriteIndex=0;}
    bool PushMessage(T element);
    T PopMessage();
    private:
    T m_FreeLockQueue[arrize];   //数组实现循环消息队列
    std::atomic<int> m_CurrentWriteIndex;   //表示当前可以写入位置，当只剩下一个空位置则不可写入
    std::atomic<int> m_CurrentReadIndex;   //表示当前可以读取数据
    inline int CountToIndex(int index);   //辅助函数，实现下标循环查找
};
template<typename T,int arrize>
inline int
CLFreeLockQueue<T,arrize>::CountToIndex(int index)
{
    return index%arrize;   //取余循环
}
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
            continue;  //队列满则一直等待到有新的位置
        if(m_CurrentWriteIndex.compare_exchange_weak(CurrentWriteIndex,NewWriteIndex))
            break;
    }while(1); //首先获取一个可以写入的位置，然后用原子操作将当前位置向后增加
    //在获取可以写入位置之后进行写入，此时该位置已经被锁定，写入不是原子操作也可以保证安全
    m_FreeLockQueue[CurrentWriteIndex] = element; 
    return true;
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
            continue ;//如果队列为空，则循环等待到队列中有消息
        if(m_CurrentReadIndex.compare_exchange_weak(CurrentReadIndex,NewReadIndex))
            break;
    }while(1);//首先获取当前可以读的位置，然后用原子操作将当前位置向后增加
    //在获取可以读位置之后进行写入，此时该位置已经被锁定，读操作不是原子操作也可以保证安全
    return m_FreeLockQueue[CurrentReadIndex];
} 
#endif