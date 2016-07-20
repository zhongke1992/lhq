#pragma once
#include "afxsock.h"

class CBody;

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
//该套接字对应的客户端的个人信息
CBody* m_pBody;

public:
	//初始化套接字。
void init();
//发送消息给客户。
void SendMsg(CMessage* pMessage);
//接收消息。
void ReceiveMsg(CMessage* pMessage);
virtual void OnReceive(int nErrorCode);
inline CArchive* GetIn() { return m_pArIn; }
inline void setBody(CBody* pBody) { m_pBody = pBody; }
inline CBody* getBody() { return m_pBody; }
	inline bool IsAborted() { return m_pArOut == NULL; }
void Abort(void);
};
