#ifndef CLSTATUS_H
#define CLSTATUS_H


/*
ÓÃÓÚ±£Žæº¯ÊýµÄŽŠÀíœá¹û
*/
class CLStatus
{
public:
	/*
	lReturnCode >=0±íÊŸ³É¹Š£¬·ñÔòÊ§°Ü
	*/
	CLStatus(long lReturnCode, long lErrorCode);
	CLStatus(const CLStatus& s);
	virtual ~CLStatus();

public:
	bool IsSuccess();
	void PrintfErrorcode();

public:
	const long& m_clReturnCode;
	const long& m_clErrorCode;

private:
	long m_lReturnCode;
	long m_lErrorCode;
};

#endif
