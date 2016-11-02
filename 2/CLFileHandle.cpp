#include <stdio.h>
#include <errno.h>  //errno
#include <unistd.h> //memset
#include <stdlib.h> //free
#include "CLFileHandle.h"
#define BUFFER_SIZE_FILE 25
#define MAX_SIZE 10
CLFileHandle::CLFileHandle()
{
    m_pFileBuffer=new char[BUFFER_SIZE_FILE];
	m_fd=-1;
	InitFilePara();

}
CLFileHandle::CLFileHandle(const char* filename,int  flag)
{
    m_pFileBuffer=new char[BUFFER_SIZE_FILE];
    OpenFile(filename,flag);
	InitFilePara();
}
CLFileHandle::~CLFileHandle()
{
    delete m_pFileBuffer;
}
CLStatus CLFileHandle::OpenFile(const char* filename,int flag)
{
    if(m_fd>0)
    {
		CloseFile();
    }
    m_fd=open(filename,flag);
    if(m_fd==-1)
    return CLStatus(-1,errno);
    InitFilePara();
    return CLStatus(1,0);
}
CLStatus CLFileHandle::WriteFile(const char* pstrMsg)
{
    if(pstrMsg == 0)
		return CLStatus(-1, 0);
	if(strlen(pstrMsg) == 0)
		return CLStatus(-1, 0);
	if(m_pFileBuffer == 0)
		return CLStatus(-1, 0);
	if(m_lastOperation==READ)
	{
		m_nUsedBytesForBuffer=0;
		lseek(m_fd,m_offset,SEEK_SET);
	}	
	m_lastOperation=WRITE;
	unsigned int nleftroom = BUFFER_SIZE_FILE - m_nUsedBytesForBuffer;
	unsigned int total_len = strlen(pstrMsg);
	if((total_len > BUFFER_SIZE_FILE) || (m_bFlagForProcessExit))
	{
		if(m_fd == -1)
			return CLStatus(-1, 0);
		ssize_t r = write(m_fd, pstrMsg, total_len);
		if(r == -1)
			return CLStatus(-1, errno);
		m_offset=lseek(m_fd,0,SEEK_CUR);
		return CLStatus(0, 0);
	}
	if(total_len > nleftroom)
	{
		CLStatus s = Flush();
		if(!s.IsSuccess())
			return CLStatus(-1, 0);
	}
	memcpy(m_pFileBuffer + m_nUsedBytesForBuffer, pstrMsg, total_len);
	m_nUsedBytesForBuffer += total_len;
	return CLStatus(0, 0);
}
CLStatus CLFileHandle::Flush()
{
    if(m_fd == -1)
		return CLStatus(-1, 0);
	if(m_pFileBuffer == 0)
		return CLStatus(-1, 0);
	if(m_nUsedBytesForBuffer == 0)
		return CLStatus(0, 0);
	ssize_t r = write(m_fd, m_pFileBuffer, m_nUsedBytesForBuffer);
	m_offset=lseek(m_fd,0,SEEK_CUR);
	if(r == -1)
		return CLStatus(-1, errno);
	m_nUsedBytesForBuffer = 0;
	m_lastOperation=FULSH;
	return CLStatus(0, 0);
}
CLStatus CLFileHandle::CloseFile()
{
    if(m_lastOperation==WRITE)
		Flush();
    int r=close(m_fd);
    if(r==-1)
    return CLStatus(-1,0);
    else
    return CLStatus(1,0);
}
CLStatus CLFileHandle:: ReadFile(char* pstrMsg,int len)
{
	if(m_pFileBuffer == 0)
		return CLStatus(-1, 0);
	if(m_lastOperation==WRITE)
		Flush();
	else if(m_lastOperation==READ)
	{
		if(len<=BUFFER_SIZE_FILE-m_nUsedBytesForBuffer)
		{
			m_offset+=len;
			memcpy(pstrMsg,m_pFileBuffer+m_nUsedBytesForBuffer,len);
			m_nUsedBytesForBuffer+=len;
			return CLStatus(1,0);
		}
		else
			lseek(m_fd,m_offset,SEEK_SET);	
	}
	m_lastOperation=READ;
	ssize_t r = read(m_fd,m_pFileBuffer,BUFFER_SIZE_FILE);
	if(r == -1)
		return CLStatus(-1, errno);
	if(r<len)
		m_offset+=r;
	else
		m_offset+=len;
	memcpy(pstrMsg,m_pFileBuffer,len);
	m_nUsedBytesForBuffer=len;
	return CLStatus(0, 0);
}
CLStatus CLFileHandle::SetFileOffset(off_t offset,int whence)
{
	if(m_lastOperation==READ)
		m_nUsedBytesForBuffer=BUFFER_SIZE_FILE;
	else if(m_lastOperation==WRITE)
		m_nUsedBytesForBuffer=0;
	m_lastOperation=LSEEK;
	int r=lseek(m_fd,offset,whence);
	if(r==-1)
		return CLStatus(-1,errno);
	m_offset=offset;
	return CLStatus(1,0);
}
off_t CLFileHandle::GetFileOffset()
{
	return m_offset;
}
void CLFileHandle::InitFilePara()
{
	m_nUsedBytesForBuffer = 0;
    m_lastOperation=NOOPERATION;
	m_offset=0;
}