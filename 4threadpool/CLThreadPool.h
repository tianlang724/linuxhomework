#ifndef  CLTHREADPOOL_H
#define CLTHREADPOOL_H
#include <vector>
#include "CLStatus.h"
#include "CLThread.h"
#include "CLThreadTask.h"
#define MAX_THREAD_NUM 10
using namespace std;


class CLThreadPool
{
    CLThreadPool(int threadnum=MAX_THREAD_NUM);
    ~CLThreadPool();
    vector<int> GetWorkThreadWriteChannel(int threadNum);
    CLStatus TerminalAll();
    CLStatus Start();
    private:
    int m_nThreadTotalNum;
    map<CLThreadWork*,bool> m_ThreadStartMap;
};

#endif