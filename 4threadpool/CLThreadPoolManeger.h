#ifndef CLTHREADPOOLMANAGER_H
#define CLTHREADPOOLMANAGER_H
#include "CLMessage.h"
class CLThreadPoolManager 
{
    CLThreadPoolManager(int threadNum=10);
    ~CLThreadPoolManager();
    void AddTask()
    void TerminalAll();
    private:
    //CLThreadPool * m_pThreadPool;
    int m_nThreadNum;

};
#endif