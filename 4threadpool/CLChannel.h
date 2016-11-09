#ifndef CLCHANNEL_H
#define CLCHANNEL_H
class CLChannel
{
    CLChannel(const char* channleName);
    ~CLChannel();
    int GetReadFd();
    int GetWriteFd();
    CLStatus InitChannel();
private:
    int m_nReadFd;
    int m_nWritFd;
    std::string m_sChannelName;
    bool m_bIsInitial;
};

#endif