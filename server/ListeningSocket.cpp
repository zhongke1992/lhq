#include "stdafx.h"
#include "ListeningSocket.h"
#include "Resource.h"
#include "serverDlg.h"

CListeningSocket::CListeningSocket(CserverDlg* pDlg)
{
m_pDlg = pDlg;
}

CListeningSocket::~CListeningSocket(void)
{
}

void CListeningSocket::OnAccept(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	CSocket::OnAccept(nErrorCode);

m_pDlg->ProcessPendingAccept();
}
