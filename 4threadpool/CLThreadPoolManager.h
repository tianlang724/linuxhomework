#ifndef CLTHREADPOOLMANAGER_H
#define CLTHREADPOOLMANAGER_H
#include "CLThreadArithmeticTask.h"
#include "CLThreadPool.h"
#include "CLStatus.h"
#include <unistd.h>
#include <vector>
#define MAX_THREAD_NUM 10
class CLThreadPoolManager 
{
public:
    CLThreadPoolManager(const char * channelName,int threadNum=MAX_THREAD_NUM);
    ~CLThreadPoolManager();
    CLStatus Initial();
    CLStatus AddTask(CLThreadTask * task);
    void TerminalAll();
    int GetCtrlThreadWriteFd();
    CLStatus ReceiveTaskReasult(int taskNum);
private:
    CLThreadPool* m_pThreadPool;
    int m_nThreadNum;
    vector<int> m_WorkThreadWriteFd;
    CLChannel *m_pCtrlChannel;
    int m_nCurThread;

};
#endif