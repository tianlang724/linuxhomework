#include "CLThreadPool.h"
CLThreadPool::CLThreadPool(int threadnum=MAX_THREAD_NUM)
{
    m_nThreadTotalNum=threadnum;
}
 CLThreadPool::~CLThreadPool()
 {
      for(int i=0;i<m_ThreadVector.size();i++)
      delete m_ThreadVector[i];
 }
CLStatus CLThreadPool::Start()
{
    CLThreadWork *p;
    for(int i=0;i<m_nThreadTotalNum;i++)
    {
        *p=new CLThreadWork();
        CLStatus s=p->Initial(i);
        if(!s.IsSuccess())
            m_ThreadStartMap(p,false);
        m_ThreadStartMap.push_back(p,true);
    }
    return CLStatus(1,0);
}
CLStatus CLThreadPool::TerminalAll()
{
    

}
