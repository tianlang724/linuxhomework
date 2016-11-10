#include "CLThreadPoolManager.h"
#include <iostream>
using namespace std;
CLThreadPoolManager::CLThreadPoolManager(const char * channelName,int threadNum)
{
    m_nThreadNum=threadNum;
    m_pThreadPool=new CLThreadPool(m_nThreadNum);
    m_pCtrlChannel=new CLChannel(channelName);
}

 CLThreadPoolManager::~CLThreadPoolManager()
 {
     delete m_pThreadPool;
 }
CLStatus CLThreadPoolManager::Initial()
{
   CLStatus s= m_pThreadPool->Initial();
   if(!s.IsSuccess())
        return CLStatus(-1,0);
    CLStatus ss=m_pCtrlChannel->InitChannel();
    if(!ss.IsSuccess())
        return CLStatus(-1,0);
    m_WorkThreadWriteFd=m_pThreadPool->GetWorkThreadWriteFd(m_nThreadNum);
    m_nCurThread=0;
}
CLStatus CLThreadPoolManager::AddTask(CLThreadTask * task)
{
    if(write(m_WorkThreadWriteFd[m_nCurThread],&task,sizeof(task))<0);
        return CLStatus(-1,0);
    m_nCurThread=(m_nCurThread+1)%m_nThreadNum;
    return CLStatus(1,0);
}
void CLThreadPoolManager::TerminalAll()
{
    
}
int CLThreadPoolManager::GetCtrlThreadWriteFd()
{
    return m_pCtrlChannel->GetWriteFd();
}
CLStatus CLThreadPoolManager::ReceiveTaskReasult(int taskNum)
{
    int num=0;
    int ret=0;
    int readFd=m_pCtrlChannel->GetReadFd();
    struct STResult result;
    do
    {
        ret=read(readFd,&result,sizeof(result));
        if(result.state)
            cout<<"task id="<<result.taskID<<" "<< "result="<<result.result<<endl;
        else 
            cout<<"calcualte error"<<endl;
        num++;
        if(num==taskNum)
            break;
    }while(ret>0);
    if(num==taskNum)
     return CLStatus(1,0);
    return CLStatus(-1,0);
}