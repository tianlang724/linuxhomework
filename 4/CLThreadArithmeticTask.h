#ifndef CLTHREADARITHMETIC_H
#define CLTHREADARITHMETIC_H
#include "CLThreadTask.h"
#define ADD 0
#define SUB 1
#define MUTIP 2
#define DIV 3
struct STResult
{
    int result;
    uint64_t taskID;
    bool state;
};
class CLThreadArithmeticTask: public CLThreadTask
{
public:
    CLThreadArithmeticTask(int fd,int op1,int op2,int type);
    ~CLThreadArithmeticTask();
    CLStatus Process();
    CLStatus PostProcess();

private:
    int m_nOp1;
    int m_nOp2;
    int m_nOpType;
    int m_nWriteBackFd;
    bool m_IsSuccess;
    int m_nResult;
};
#endif