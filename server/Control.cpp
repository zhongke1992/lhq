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
	void CControl::getBodies(vector<CClientSocket*>* pSockets, vector<CBody*>& pBodies)
	{
		vector<CClientSocket*>::iterator iter;
		for (iter=pSockets->begin();iter!=pSockets->end();iter++)
	{
CClientSocket* pSocket = *iter;
CBody* pBody = pSocket->getBody();
if (NULL != pBody)
{
	pBodies.push_back(pBody);
}
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
	void CControl::closeSocket(vector<CClientSocket*>* pSockets, CClientSocket* pSocket)
	{
		vector<CClientSocket*>::iterator iter;

		for (iter=pSockets->begin();iter!=pSockets->end();iter++)
		{
		CClientSocket* pSock = *iter;

		if (pSock == pSocket)
		{
			pSockets->erase(iter);
		break;
		}//if
		}//for
		}

	/**
	������Ϣ��һ���ˡ�
	* @param pSockets Ҫ���͸����˵��б�
	* @param pMessage Ҫ���͵���Ϣ��
* @return void
*/
	void CControl::sendMessage(vector<CClientSocket*>* pSockets, CMessage* pMessage)
	{
		vector<CClientSocket*>::iterator iter;
		for (iter=pSockets->begin();iter!=pSockets->end();iter++)
{
CClientSocket* pSocket = *iter;
m_pDlg->SendMsg(pSocket, pMessage);
}//for
	}
