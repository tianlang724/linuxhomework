#include <iostream>
#include "CLThread.h"
#include "CLExecutiveFunctionProvider.h"
#include "CLMessageQueueBySTLqueue.h"
#include "CLMessage.h"
#include "CLMsgLoopManagerForSTLqueue.h"
#include "CLMessageObserver.h"
#include "CLFreeLockQueue.h"
#include "CLFreeLockQueueManage.h"

using namespace std;

#define ADD_MSG 0
#define QUIT_MSG 1

class CLMyMsgProcessor;

class CLAddMessage : public CLMessage
{
public:
	friend class CLMyMsgProcessor;

	CLAddMessage(int Op1, int Op2):CLMessage(ADD_MSG)
	{
		m_Op1 = Op1;
		m_Op2 = Op2;
	}

	virtual ~CLAddMessage()
	{
	}

private:
	int m_Op1;
	int m_Op2;
};

class CLQuitMessage : public CLMessage
{
public:
	CLQuitMessage() : CLMessage(QUIT_MSG)
	{
	}

	virtual ~CLQuitMessage()
	{
	}
};

class CLMyMsgProcessor : public CLMessageObserver
{
public:
	CLMyMsgProcessor()
	{
	}

	virtual ~CLMyMsgProcessor()
	{
	}

	virtual CLStatus Initialize(void* pContext)
	{
		return CLStatus(0, 0);
	}

	virtual CLStatus DispatchMessage(CLMessage *pM)
	{
		CLAddMessage *pAddMsg;
		switch(pM->m_clMsgID)
		{
		case ADD_MSG:
			pAddMsg = (CLAddMessage *)pM;
			cout << pAddMsg->m_Op1 + pAddMsg->m_Op2 << endl;
			break;

		case QUIT_MSG:
			cout << "quit..." << endl;
			return CLStatus(QUIT_MESSAGE_LOOP, 0);

		default:
			break;
		}

		return CLStatus(0, 0);
	}
};

class CLAdder: public CLExecutiveFunctionProvider
{
	CLMessageLoopManager *m_pMsgLoopManager;

public:
	CLAdder(CLMessageLoopManager *pMsgLoopManager)
	{
		m_pMsgLoopManager = pMsgLoopManager;
	}

	virtual ~CLAdder()
	{
		if(m_pMsgLoopManager != 0)
			delete m_pMsgLoopManager;
	}
	
	virtual CLStatus RunExecutiveFunction(void* pContext)
	{
		return m_pMsgLoopManager->EnterMessageLoop(pContext);	
	}
};

int main()
{
	CLFreeLockQueue<CLMessage*> *pQ=new CLFreeLockQueue<CLMessage*>();
	CLThread *t = new CLThread(new CLAdder(new CLFreeLockQueueManage(new CLMyMsgProcessor(), pQ)), true);
	t->Run(0);
	for(int i=0;i<100;i++)
	{
	CLAddMessage *paddmsg = new CLAddMessage(i,i);
	pQ->PushMessage(paddmsg);
	}
	CLQuitMessage *pquitmsg = new CLQuitMessage();
	pQ->PushMessage(pquitmsg);
	t->WaitForDeath();  
	return 0;
}
