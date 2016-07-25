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
	void CControl::closeSocket(CClientSocket* pSocket)
	{
	m_pDlg->CloseSocket(pSocket);
	}