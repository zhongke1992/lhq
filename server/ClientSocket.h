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
	//��ʼ���׽��֡�
void init();
//������Ϣ���ͻ���
void SendMsg(CMessage* pMessage);
//������Ϣ��
void ReceiveMsg(CMessage* pMessage);
virtual void OnReceive(int nErrorCode);
inline CArchive* GetIn() { return m_pArIn; }
};
