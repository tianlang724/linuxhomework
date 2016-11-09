#include "CLThreadTask.h"

CLThreadTask::CLThreadTask()
{

}
CLThreadTask::~CLThreadTask()
{

}
CLStatus CLThreadTask::PreProcess()
{
    return CLStatus(1,0);
}
CLStatus CLThreadTask::Process()
{
    return CLStatus(1,0);
}
CLStatus CLThreadTask::PostProcess()
{
    return CLStatus(1,0);
}
CLStatus CLThreadTask::SetTaskID(uint64_t id)
{
    m_nTaskID=id;
    return CLStatus(1,0);
}
uint64_t CLThreadTask::GetTaskID()
{
    return m_nTaskID;
}