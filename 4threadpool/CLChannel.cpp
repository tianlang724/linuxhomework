#include<sys/types.h>
#include<sys/stat.h>
#include <errno.h>
#include "CLChannel.h"
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

using namespace std;
CLChannel::CLChannel(const char* channleName):m_sChannelName(channelName)
{
    m_nReadFd=-1;
    m_nWritFd=-1;
    m_bIsInitial=false;
}
CLChannel::~CLChannel()
{

}
CLStatus CLChannel::InitChannel()
{
    if((mkfifo(m_sChannelName.c_str() , FILE_MODE ) < 0) && (errno != EEXIST) ){
        return CLStatus(-1,0);
    }
    m_bIsInitial=true;
    return CLStatus(1,0);
}
int GetReadFd()
{
    if(!m_bIsInitial)
        return -1;
    if(m_nReadFd==-1)
    {
        m_nReadFd=open(m_sChannelName.c_str(),O_RDWR,0);
    }
    return m_nReadFd;
}
int GetWriteFd()
{
    if(!m_bIsInitial)
        return -1;
    if(m_nWritFd==-1)
    {
        m_nWritFd=open(m_sChannelName.c_str(),O_RDWR,0);
    }
    return m_nWritFd;
}