#include "CLThreadPool.h"
using namespace std;
CLThreadPool::CLThreadPool(int threadnum)
{
    m_nThreadTotalNum=threadnum;
}
 CLThreadPool::~CLThreadPool()
 {

 }
CLStatus CLThreadPool::Initial()
{
    CLThreadWork *p;
    for(int i=0;i<m_nThreadTotalNum;i++)
    {
        *p=new CLThreadWork(false);
        CLStatus s=p->Initial(i);
        if(!s.IsSuccess())
        {
            return CLStatus(-1,0);
        }
       p->Run(NULL);
       m_ThreadStartMap[p]=true;
    }
    return CLStatus(1,0);
}
CLStatus CLThreadPool::TerminalAll()
{
    

}
vector<int> CLThreadPool::GetWorkThreadWriteFd(int threadNum)
{
    vector<int> threadChannelVector;
    map<CLThreadWork*,bool>::iterator it,itend;
    it=m_ThreadStartMap.begin();
    itend=m_ThreadStartMap.end();
    int i=0;
    for(;it!=itend;it++)
    {
        if(it->second)
        {
            threadChannelVector.push_back(it->first->GetChannelWriteFd());
            it->second=false;
        }
        i++;
        if(i==threadNum)
        break;
    }
    return threadChannelVector;
}
