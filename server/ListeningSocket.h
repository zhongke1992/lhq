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

	//数据成员
CserverDlg* m_pDlg;
};
