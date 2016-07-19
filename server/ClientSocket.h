#pragma once
#include "afxsock.h"

class CserverDlg;
class CMessage;

class CClientSocket :
	public CSocket
{
public:
	CClientSocket(CserverDlg* pDlg);
	~CClientSocket(void);

private:
	CSocketFile *m_pFile;
CArchive* m_pArIn;
CArchive* m_pArOut;
CserverDlg* m_pDlg;

public:
	//初始化套接字。
void init();
//发送消息给客户。
void SendMsg(CMessage* pMessage);
//接收消息。
void ReceiveMsg(CMessage* pMessage);
virtual void OnReceive(int nErrorCode);
inline CArchive* GetIn() { return m_pArIn; }
};
