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
	// TODO: �ڴ����ר�ô����/����û���
	CSocket::OnAccept(nErrorCode);

m_pDlg->ProcessPendingAccept();
}
