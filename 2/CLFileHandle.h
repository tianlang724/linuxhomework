#ifndef CLFILEHANDLE_H
#define CLFILEHANDLE_H
#include <string.h>
#include <fcntl.h>
#include "CLStatus.h"
#define NOOPERATION 0
#define READ 1
#define WRITE 2
#define LSEEK 3
#define FULSH 4
/***************************
需要提供open/read/write/lseek/close等函数的封装函数
该类要提供数据缓存服务。
调用该类的写操作接口时，数据要首先写到缓存，然后再根据策略写到文件中。
调用该类的读操作接口时，该类能根据策略缓存读出的数据
读写缓存要保持一致性
***************************/

class CLFileHandle
{
    public:
    CLFileHandle();
    CLFileHandle(const char* filename,int  flag);
    ~CLFileHandle();
    CLStatus OpenFile(const char* filename,int flag);
    CLStatus WriteFile(const char* pstrMsg);
    CLStatus ReadFile(char* pstrMsg,int len);
    CLStatus SetFileOffset(off_t offset,int whence);
    off_t GetFileOffset();
    CLStatus CloseFile();
    private:
    int m_fd;
    off_t m_offset;
    char *m_pFileBuffer;
    int m_lastOperation;
	unsigned int m_nUsedBytesForBuffer;
    bool m_bFlagForProcessExit;
    void ClearFileBuffer();
    CLStatus Flush();
    void InitFilePara();
};
#endif