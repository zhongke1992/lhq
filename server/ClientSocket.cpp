#include "StdAfx.h"
#include "ClientSocket.h"
#include "../include/message/Message.h"
#include "Resource.h"
#include "serverDlg.h"

CClientSocket::CClientSocket(CserverDlg* pDlg)
{
m_pDlg = pDlg;
m_pFile = NULL;
m_pArIn = NULL;
m_pArOut = NULL;
}

CClientSocket::~CClientSocket(void)
{
if (NULL != m_pFile)
delete m_pFile;

if (NULL != m_pArIn)
delete m_pArIn;

if (NULL != m_pArOut)
delete m_pArOut;
}

void CClientSocket::init()
{
	//建立CSocketFile，发送和接受序列化，并关联。
m_pFile = new CSocketFile(this);
m_pArIn = new CArchive(m_pFile, CArchive::load);
m_pArOut = new CArchive(m_pFile, CArchive::store);
}

void CClientSocket::SendMsg(CMessage* pMessage)
{
	if (NULL != m_pArOut) {
	pMessage->Serialize(*m_pArOut);
m_pArOut->Flush();
	}
}

void CClientSocket::ReceiveMsg(CMessage* pMessage)
{
pMessage->Serialize(*m_pArIn);
}


void CClientSocket::OnReceive(int nErrorCode)
{
	CSocket::OnReceive(nErrorCode);

// TODO: 在此添加专用代码和/或调用基类
m_pDlg->ProcessPendingRead(this);	
}