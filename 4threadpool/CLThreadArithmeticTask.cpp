#include "CLThreadArithmeticTask.h"
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
        m_nReasult=m_nOp1+m_nOp2;
        break;
        case SUB:
        m_nReasult=m_nOp1-m_nOp2;
        break;
        case MUTIP:
        m_nReasult=m_Op1*m_nOp2;
        break;
        case DIV:
        if(m_nOp2==0)
        {
                 m_IsSucess=false;
                 m_nReasult=-1;
                return CLStatus(-1,0);
        }
        m_nReasult=m_nOp1/m_nOp2;
        break;
        default:
        return CLStatus(-1,0);
    }
    m_IsSucess=true;
    return CLStatus(1,0);
}
CLStatus PostProcess()
{
    struct STResult result;
    result.result=m_nReasult;
    result.state=m_IsSucess;
    result.taskID=this->GetTaskID();
    if(write(m_nWriteBackFd,&result,sizeof(struct STResult))<0)
        return CLStatus(-1,0);
    return CLStatus(1,0);

}
