#ifndef  CLTHREADPOOL_H
#define CLTHREADPOOL_H
#include <vector>
#include <map>
#include "CLStatus.h"
#include "CLThreadWork.h"
#include "CLThreadTask.h"
#define MAX_THREAD_NUM 10
using namespace std;


class CLThreadPool
{
public:
    CLThreadPool(int threadnum=MAX_THREAD_NUM);
    ~CLThreadPool();
    vector<int> GetWorkThreadWriteFd(int threadNum);
    CLStatus TerminalAll();
    CLStatus Initial();
    int GetThreadNum();
private:
    int m_nThreadTotalNum;
    map<CLThreadWork*,bool> m_ThreadStartMap;
};

#endif