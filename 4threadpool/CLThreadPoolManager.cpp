#include "CLThreadPoolManager.h"
using namespace std;
CLThreadPoolManager::CLThreadPoolManager(int threadNum=10)
{
    m_nThreadNum=threadNum;
    m_pThreadPool=new threadPool(m_ThreadNum);
}

 CLThreadPoolManager::~CLThreadPoolManager()
 {
     delete m_pThreadPool;
 }
void CLThreadPoolManager::AddMessage(CLMessage *msg)
{
    m_pThreadPool->AddMessage(CLMessage *msg);
}
void CLThreadPoolManager::TerminalAll()
{
    m_pThreadPool->TerminalALL();
}