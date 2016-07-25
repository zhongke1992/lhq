#include "stdafx.h"
#include "Control.h"
#include "Resource.h"
#include "clientDlg.h"

 CControl* CControl::m_pControl = NULL;

CControl::CControl(void)
{
m_pDlg = NULL;
}

CControl::~CControl(void)
{
}

CControl* CControl::getInstance()
	{
	if (NULL == m_pControl)
		m_pControl = new CControl();
	return m_pControl;
	}

/**
用于下层控制关闭通讯套接字。
* @param void
* @return void
*/
void CControl::closeSocket()
{
m_pDlg->closeSocket();
}

/**
下层调用，用于弹出对话框。
* @param szText 对话框的文本
* @param szTitle 对话框的标题。
* @param type 产生的对话框ID。
* @param type 产生的对话框类型。
* @return int 返回对话框返回的信息。
*/
int CControl::messageBox(CString szText, CString szTitle, int type)
{
if (""==szTitle && 0==type)
	return m_pDlg->MessageBox(szText);
else if (0==type)
	return m_pDlg->MessageBox(szText, szTitle);
else
	return m_pDlg->MessageBox(szText, szTitle, type);
}