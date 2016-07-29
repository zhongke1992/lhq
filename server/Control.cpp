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
	* 获取到所有套接字中的CBody对象的指针。
	* @param pBodies 用来获取指针的容器。
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
	发送消息给某个客户端。
	* @param pSocket 要发送到的消息结构体。
	* @param pMessage 发送的消息。
	* @retgurn void
	*/
	void CControl::sendMessage(CClientSocket* pSocket, CMessage* pMessage)
	{
	m_pDlg->SendMsg(pSocket, pMessage);
	}

	/**
	关闭某客户端套接字
* @param pSocket 要关闭的客户端套接字。
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
	发送消息给一组人。
	* @param pSockets 要发送给的人的列表。
	* @param pMessage 要发送的消息。
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
