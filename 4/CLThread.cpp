#include "CLThread.h"
#include <iostream>
using namespace std;
CLThread::CLThread(bool bWaitForDeath)
{
    m_bCreatedThread=false;
    m_bWaitForDeath=bWaitForDeath;

}
CLThread::~CLThread()
{

}
CLStatus CLThread::Run(void* pContext)
{
    if(m_bCreatedThread)
        return CLStatus(-1,0);
    m_pContext=pContext;
    int ret=pthread_create(&m_ThreadID,NULL,StartFunctionOfThread,this);
    if(ret<0)
        return CLStatus(-1,0);
    m_bCreatedThread=true;
    if(!m_bWaitForDeath)
    {
	        ret = pthread_detach(m_ThreadID);
	        if(ret!= 0)
              return CLStatus(-1,0);
	}
    return CLStatus(1,0);

       
}
void* CLThread::StartFunctionOfThread(void *pContext)
{
    CLThread *pThread=(CLThread*)pContext;
    pThread->RunThreadFunction();
    return 0;
}
CLStatus CLThread::WaitForDeath()
{
    if(!m_bCreatedThread)
        return CLStatus(-1,0);
    if(!m_bWaitForDeath)
        return CLStatus(-1,0);
    int ret=pthread_join(m_ThreadID,0);
    if(ret!=0)
        return CLStatus(-1,0);
    delete this;
    return CLStatus(1,0);
}
