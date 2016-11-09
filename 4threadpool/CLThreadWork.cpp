#include "CLThreadWork.h"
#include <errno.h>
using namespace std;
CLThreadWork::CLThreadWork(bool bWaitForDeath )::CLThread(bWaitForDeath)
{
    m_pChannel=NULL;
    m_pThreadTask=NULL;
    m_nWriteBackFd=-1;
}
CLThreadWork::~CLThreadWork()
{

}
CLStatus CLThreadWork::Initial(int channelNum)
{
    char pathName[20];
    sprintf(pathName, "%d.fifo", channelNum);
    m_pChannel = new FIFOChannel(pathName);  
    CLStatus s=m_pChannel->Initial();
    if(!s.IsSuccess)
        return CLStatus(-1,0);

    return CLStatus(1,0);
}
int CLThreadWork::GetChannelWriteFd()
{
    if(m_pChannel==NULL)
        return -1;
    return m_pChannel->GetWriteFd();
}
CLStatus CLThreadWork::RunThreadFunction()
{
    int readfd=m_pChannel->GetReadFd();
    while(read(readfd,&m_pThreadTask,sizeof(m_pThreadTask)>0))
    {
        m_pThreadTask->PreProcess();
        m_pThreadTask->Process();
        m_pThreadTask->postProcess();
        delete m_pThreadTask;
    }
    return CLStatus(1,0);

}
