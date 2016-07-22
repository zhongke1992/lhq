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
inline CArchive* getOut() { return m_pArOut; }
inline CArchive* getIn() { return m_pArIn; }

/**
调用用以接收消息。
* @param pMessage 接收消息的结构体。
* @return void
*/
void ReceiveMsg(CMessage* pMessage);
};
