#ifndef CLCHANNEL_H
#define CLCHANNEL_H
#include "CLStatus.h"
#include <string>
using namespace std;
class CLChannel
{
public:
    CLChannel(const char* channelName);
    ~CLChannel();
    int GetReadFd();
    int GetWriteFd();
    CLStatus InitChannel();
private:
    int m_nReadFd;
    int m_nWritFd;
    string m_sChannelName;
    bool m_bIsInitial;
};

#endif