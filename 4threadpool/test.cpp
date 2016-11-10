#include "CLThreadPoolManager.h"
#include "CLThreadArithmeticTask.h"
#include "CLStatus.h"
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
using namespace std;
int main()
{
    struct timeval begin,end;
    CLThreadPoolManager *pPoolManager=new CLThreadPoolManager("ctrl.fifo",10);
    CLStatus s=pPoolManager->Initial();
    if(!s.IsSuccess())
        return 0;
    int nctrlwritefd=pPoolManager->GetCtrlThreadWriteFd();
    gettimeofday(&begin,NULL);
    for(int i=0;i<2000;i++)
    {
        CLThreadTask *pTask=new CLThreadArithmeticTask(nctrlwritefd,i,i,ADD);
        pTask->SetTaskID(i);
        pPoolManager->AddTask(pTask);
    }
    pPoolManager->ReceiveTaskReasult(2000);
    gettimeofday(&end,NULL);
    cout << "10 thread time spend: "<< ( end.tv_sec - begin.tv_sec ) * 1000000 + end.tv_usec - begin.tv_usec << " us" <<endl;
}
