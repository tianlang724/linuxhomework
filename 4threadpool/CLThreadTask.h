#ifndef CLTHREADTASK_H
#define CLTHREADTASK_H
#include "CLStatus.h"
class CLThreadTask
{
    CLThreadTask();
    ~CLThreadTask();
    virtual CLStatus PreProcess();
    virtual CLStatus Process();
    virtual CLStatus PostProcess();
    CLStatus SetTaskID(uint64_t id);
    uint64_t GetTaskID() const;
    private:
    uint64_t m_nTaskID;
};
#endif