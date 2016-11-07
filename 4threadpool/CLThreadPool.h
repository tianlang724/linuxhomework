#ifndef  CLTHREADPOOL_H
#define CLTHREADPOOL_H
#include <vector>
#include "CLStatus.h"
#include "CLThread.h"
#include "CLMessageLoopManager.h"
#include "CLMessageQueueBySTLqueue.h"
#include "CLExecutiveFunctionForMsgLoop.h"
#include "CLMsgLoopManagerForSTLqueue.h"
#include "CLMessageObserver.h"
#define MAX_THREAD_NUM 10
using namespace std;

template<typename observer>
class CLThreadPool
{
    CLThreadPool(int threadnum=MAX_THREAD_NUM);
    ~CLThreadPool();
    CLStatus AddMessage(CLMessage *msg,int i);
    CLStatus TerminalAll();
    CLStatus Start();
    private:
    int m_threadNum;
    vector<CLThread*> m_ThreadVector;
    vector<CLMessageQueueBySTLqueue*> m_ThreadMessageQueue;
};
template<typename observertype>
CLThreadPool<observertype>::CLThreadPool(int threadnum)
{
    m_threadNum=threadnum;
    for(int i=0;i<m_threadNum;i++)
    {
        CLMessageQueueBySTLqueue *pQ = new CLMessageQueueBySTLqueue();
        observertype *pOberver=new observertype();
        CLMsgLoopManagerForSTLqueue *pstlqueue=new CLMsgLoopManagerForSTLqueue((CLMessageObserver*)pOberver,pQ);
        CLExecutiveFunctionForMsgLoop *pLoop=new CLExecutiveFunctionForMsgLoop(pstlqueue);
        CLThread *t = new CLThread(pLoop,true);
        m_ThreadVector.push_back(t);
        m_ThreadMessageQueue.push_back(pQ);
    }
}
template<typename observertype>
 CLThreadPool<observertype>::~CLThreadPool()
 {
      for(int i=0;i<m_ThreadVector.size();i++)
      delete m_ThreadVector[i];
 }
template<typename observertype>
CLStatus 
CLThreadPool<observertype>::AddMessage(CLMessage *msg,int i)
{
    int num=i%MAX_THREAD_NUM;
    pQ[num]->Push(msg);

}
template<typename observertype>
CLStatus 
CLThreadPool<observertype>::TerminalAll()
{

}
template<typename observertype>
CLStatus 
CLThreadPool<observertype>::Start()
{
    for(int i=0;i<m_ThreadVector.size();i++)
    m_ThreadVector[i]->Run(0);
}  


/*
class CLThreadPool
{
    CLThreadPool(int threadnum=MAX_THREAD_NUM,CLMessageObserver *p_CLMessageObserver);
    ~CLThreadPool();
    CLStatus AddMessage(CLMessage *msg);
    CLStatus TerminalAll();
    CLStatus Start();
    private:
    int m_threadNum;
    vector<CLThread*> m_ThreadVector;
    CLMessageQueueBySTLqueue *m_pMessageQueueBySTLqueue;
};
CLThreadPool::CLThreadPool(int threadnum=MAX_THREAD_NUM)
{
    m_pMessageQueueBySTLqueue = new CLMessageQueueBySTLqueue();
    CLMsgLoopManagerForSTLqueue *pstlqueue=new CLMsgLoopManagerForSTLqueue(p_CLMessageObserver,m_pMessageQueueBySTLqueue);
    CLExecutiveFunctionForMsgLoop *pLoop=new CLExecutiveFunctionForMsgLoop(pstlqueue);
    CLThread *t ;
    for(int i=0;i<m_threadNum;i++)
    {
       
        t = new CLThread(pLoop,true);
        m_ThreadVector.push_back(t);
    }
}
 CLThreadPool::~CLThreadPool()
 {
      for(int i=0;i<m_ThreadVector.size();i++)
      delete m_ThreadVector[i];
 }
 CLStatus  CLThreadPool::AddMessage(CLMessage *msg)
 {
     m_pMessageQueueBySTLqueue->Push(msg);
 }
CLStatus CLThreadPool::Start()
{
    for(int i=0;i<m_ThreadVector.size();i++)
       m_ThreadVector[i]->Run(0);
}
CLStatus CLThreadPool::TerminalAll()
{
    //???

}

*/

#endif