#ifndef CLFREELOCKQUEUEMANAGE_H
#define CLFREELOCKQUEUEMANAGE_H
#include "CLMessageObserver.h"
#include "CLFreeLockQueue.h"
#include "CLMessageLoopManager.h"
class CLFreeLockQueueManage: public CLMessageLoopManager
{
public:
	CLFreeLockQueueManage(CLMessageObserver *pMsgObserver, CLFreeLockQueue<CLMessage*> *pMsgQueue);
	virtual ~CLFreeLockQueueManage();
protected:
	virtual CLStatus Initialize();
	virtual CLStatus Uninitialize();	
	virtual CLMessage* WaitForMessage();
private:
    CLFreeLockQueue<CLMessage*> *m_pMsgQueue;
};
#endif