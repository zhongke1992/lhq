#include "stdafx.h"
#include "Resource.h"
#include "Control.h"
#include "serverDlg.h"

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
	* ��ȡ�������׽����е�CBody�����ָ�롣
	* @param pBodies ������ȡָ���������
	* @return void.
	*/
	void CControl::getPbodies(CPtrList& pBodies)
	{
	if (NULL == m_pDlg)
		return;
//const CserverDlg* pDlg = m_pDlg;
	CPtrList* pConnectionList = m_pDlg->getConnectionList();

	for (POSITION pos=pConnectionList->GetHeadPosition();pos!=NULL;)
	{
CClientSocket* pSocket = (CClientSocket*)pConnectionList->GetNext(pos);
CBody* pBody = pSocket->getBody();
if (NULL != pBody)
pBodies.AddTail(pBody);
	}//for
	
	}

	/**
	������Ϣ��ĳ���ͻ��ˡ�
	* @param pSocket Ҫ���͵�����Ϣ�ṹ�塣
	* @param pMessage ���͵���Ϣ��
	* @retgurn void
	*/
	void CControl::sendMessage(CClientSocket* pSocket, CMessage* pMessage)
	{
	m_pDlg->SendMsg(pSocket, pMessage);
	}

	/**
	�ر�ĳ�ͻ����׽���
* @param pSocket Ҫ�رյĿͻ����׽��֡�
* @return void
*/
	void CControl::closeSocket(CClientSocket* pSocket)
	{
	m_pDlg->CloseSocket(pSocket);
	}