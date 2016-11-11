#include "CLThreadArithmeticTask.h"
#include <unistd.h>
CLThreadArithmeticTask::CLThreadArithmeticTask(int fd,int op1,int op2,int type):
m_nWriteBackFd(fd),m_nOp1(op1),m_nOp2(op2),m_nOpType(type)
{
}
CLThreadArithmeticTask::~CLThreadArithmeticTask()
{

}
CLStatus CLThreadArithmeticTask::Process()
{
    switch(m_nOpType)
    {
        case ADD:
        m_nResult=m_nOp1+m_nOp2;
        break;
        case SUB:
        m_nResult=m_nOp1-m_nOp2;
        break;
        case MUTIP:
        m_nResult=m_nOp1*m_nOp2;
        break;
        case DIV:
        if(m_nOp2==0)
        {
                 m_IsSuccess=false;
                 m_nResult=-1;
                return CLStatus(-1,0);
        }
        m_nResult=m_nOp1/m_nOp2;
        break;
        default:
        return CLStatus(-1,0);
    }
    m_IsSuccess=true;
    return CLStatus(1,0);
}
CLStatus CLThreadArithmeticTask::PostProcess()
{
    struct STResult result;
    result.result=m_nResult;
    result.state=m_IsSuccess;
    result.taskID=this->GetTaskID();
    if(write(m_nWriteBackFd,&result,sizeof(struct STResult))<0)
        return CLStatus(-1,0);
    return CLStatus(1,0);

}
