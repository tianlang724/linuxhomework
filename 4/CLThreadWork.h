#ifndef CLTHREADWORK_H
#define CLTHREADWORK_H
#include "CLStatus.h"
#include "CLThread.h"
#include "CLChannel.h"
#include "CLThreadTask.h"
class CLThreadWork:public CLThread
{
public:
    CLThreadWork( bool bWaitForDeath);
    ~CLThreadWork();
    CLStatus RunThreadFunction( void );
    CLStatus Initial(int channelNum); 
    int GetChannelWriteFd();
private:
    CLChannel *m_pChannel;
    CLThreadTask *m_pThreadTask;
    int m_nWriteBackFd;
};
#endif