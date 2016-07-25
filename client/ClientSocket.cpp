#include "StdAfx.h"
#include "ClientSocket.h"
#include "Resource.h"
#include "clientDlg.h"

CClientSocket::CClientSocket(CclientDlg* pDlg)
{
m_pDlg = pDlg;
}

CClientSocket::~CClientSocket(void)
{
	if (NULL != m_pArIn)
		delete m_pArIn;
	m_pArIn = NULL;

	if (NULL != m_pArOut)
		delete m_pArOut;
	m_pArOut = NULL;

if (NULL != m_pFile)
	delete m_pFile;
m_pFile = NULL;
}

void CClientSocket::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类

	CSocket::OnReceive(nErrorCode);
m_pDlg->ProcessPendingRead();
}

void CClientSocket::init()
{
m_pFile = new CSocketFile(this);
m_pArIn = new CArchive(m_pFile, CArchive::load);
m_pArOut = new CArchive(m_pFile, CArchive::store);
}

void CClientSocket::SendMsg(CMessage* pMessage)
{
TRY
{
pMessage->Serialize(*m_pArOut);
m_pArOut->Flush();
}
CATCH(CFileException, e)
{
}
END_CATCH
}

/**
调用用以接收消息。
* @param pMessage 接收消息的结构体。
* @return void
*/
void CClientSocket::ReceiveMsg(CMessage* pMessage)
{
TRY
	{
					pMessage->Serialize(*m_pArIn);
}
	CATCH(CFileException, e)
	{
		m_pArOut->Abort();
	}
		END_CATCH
}
