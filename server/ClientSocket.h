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
//���׽��ֶ�Ӧ�Ŀͻ��˵ĸ�����Ϣ
CBody* m_pBody;

public:
	//��ʼ���׽��֡�
void init();
//������Ϣ���ͻ���
void SendMsg(CMessage* pMessage);
//������Ϣ��
void ReceiveMsg(CMessage* pMessage);
virtual void OnReceive(int nErrorCode);
inline CArchive* GetIn() { return m_pArIn; }
inline void setBody(CBody* pBody) { m_pBody = pBody; }
inline CBody* getBody() { return m_pBody; }
	inline bool IsAborted() { return m_pArOut == NULL; }
void Abort(void);
};
