#include "CLFreeLockQueueManage.h"
CLFreeLockQueueManage::CLFreeLockQueueManage(CLMessageObserver *pMsgObserver, CLFreeLockQueue<CLMessage*> *pMsgQueue): CLMessageLoopManager(pMsgObserver)
{
    m_pMsgQueue = pMsgQueue;
}
CLFreeLockQueueManage::~CLFreeLockQueueManage()
{
    	delete m_pMsgQueue;
}

CLStatus CLFreeLockQueueManage::Initialize()
{
    return CLStatus(1,0);
}
CLStatus CLFreeLockQueueManage::Uninitialize()
{
    return CLStatus(1,0);
}
CLMessage* CLFreeLockQueueManage::WaitForMessage()
{
    return m_pMsgQueue->PopMessage();
}