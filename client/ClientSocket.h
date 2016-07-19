#pragma once
#include "afxsock.h"

class CclientDlg;
class CMessage;

class CClientSocket :
	public CSocket
{
public:
	CClientSocket(CclientDlg* pDlg);
	~CClientSocket(void);

private:
CclientDlg* m_pDlg;
CSocketFile* m_pFile;
CArchive* m_pArIn;
CArchive* m_pArOut;

public:
	virtual void OnReceive(int nErrorCode);
void init();
void SendMsg(CMessage* pMessage);
};
