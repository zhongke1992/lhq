#pragma once
#include "afxsock.h"

class CserverDlg;

class CListeningSocket :
	public CSocket
{
public:
	CListeningSocket(CserverDlg* pDlg);
	~CListeningSocket(void);
	virtual void OnAccept(int nErrorCode);

	//���ݳ�Ա
CserverDlg* m_pDlg;
};
