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
}

void CClientSocket::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类

	CSocket::OnReceive(nErrorCode);
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
delete pMessage;
}
CATCH(CFileException, e)
{
}
END_CATCH
}
