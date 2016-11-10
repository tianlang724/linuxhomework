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
    CLThreadPoolManager *pPoolManager=new CLThreadPoolManager("ctrl",5);
    CLStatus s=pPoolManager->Initial();
    if(!s.IsSuccess())
        return 0;

    int nctrlwritefd=pPoolManager->GetCtrlThreadWriteFd();
    struct timeval begin,end;
    for(int i=0;i<1000;i++)
    {
        CLThreadTask *pTask=new CLThreadArithmeticTask(nctrlwritefd,i,i,ADD);
        pTask->SetTaskID(i);
        pPoolManager->AddTask(pTask);
    }
    pPoolManager->ReceiveTaskReasult(1000);
    gettimeofday(&end,NULL);
    cout << "time spend: "<< ( end.tv_sec - begin.tv_sec ) * 1000000 + end.tv_usec - begin.tv_usec << " us" <<endl;

}