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
�����²���ƹر�ͨѶ�׽��֡�
* @param void
* @return void
*/
void CControl::closeSocket()
{
m_pDlg->closeSocket();
}

/**
�²���ã����ڵ����Ի���
* @param szText �Ի�����ı�
* @param szTitle �Ի���ı��⡣
* @param type �����ĶԻ���ID��
* @param type �����ĶԻ������͡�
* @return int ���ضԻ��򷵻ص���Ϣ��
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