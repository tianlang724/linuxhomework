#ifndef CLTHREAD_H
#define CLTHREAD_H
#include "CLStatus.h"
class CLThread
{
    CLThread(bool bWaitForDeath);
    ~CLThread();
    CLStatus Run(void *pContext);
    static void *StartFunctionOfThread(void *pContext);
    CLStatus WaitForDeath();
protected:
    virtual CLStatus RunThreadFunction( void ) = 0;
    void *m_pContext;
    pthread_t m_ThreadID;
    bool m_bWaitForDeath;
    bool m_bCreatedThread;
};
#endif