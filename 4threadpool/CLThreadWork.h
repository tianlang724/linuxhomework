#ifndef CLTHREADWORK_H
#define CLTHREADWORK_H
#include "CLThread.h"
class CLThreadWork:public CLThread
{
    CLThreadWork( bool bWaitForDeath);
    ~CLThreadWork();

    private:
    CLExecutiveFunctionProvider *m_pExecutiveFunctionProvider;
}
#endif