#include "CLFreeLockQueue.h"
/*
template<typename T,int arrize>
CLFreeLockQueue<T,arrize>::CLFreeLockQueue()
{
    m_CurrentReadIndex=0;
    m_CurrentWriteIndex=0;
}
*/
template<typename T,int arrize>
inline int
CLFreeLockQueue<T,arrize>::CountToIndex(int index)
{
    return index%arrize;
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
            return false;
        //compare_exchange_weak (T& expected, T val）
        //相等，则用 val 替换原子对象的旧值。
        //不相等，则用原子对象的旧值替换 expected ，因此调用该函数之后，如果被该原子对象封装的值与参数 expected 所指定的值不相等，
        //expected 中的内容就是原子对象的旧值。
        if(m_CurrentWriteIndex.compare_exchange_weak(CurrentWriteIndex,NewWriteIndex))
            break;
    }while(1);
    m_FreeLockQueue[CurrentWriteIndex] = element;
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
            return NULL;
        if(m_CurrentReadIndex.compare_exchange_weak(CurrentReadIndex,NewReadIndex))
            break;
    }while(1);
    return m_FreeLockQueue[CurrentReadIndex];
    
} 

