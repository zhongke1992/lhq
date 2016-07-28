#include "stdafx.h"
#include "SystemMessageDeal.h"
#include "../include/message/Message.h"
#include "ClientSocket.h"
#include "Control.h"
#include "Body.h"


CSystemMessageDeal::CSystemMessageDeal(unsigned int min, unsigned int max)
	:CMessageChain(min, max)
{
}

CSystemMessageDeal::~CSystemMessageDeal(void)
{
}

/**
	当客服端发来数据处理
	* @param pSockets 桌面玩家套接字列表
	* @param pSocket 发送来消息的客户端套接字
	* @param pMessage 发送的消息结构体
	* @param pControl 上层控制接口
	*/
	void CSystemMessageDeal::dataCome(CPtrList* pSockets, CClientSocket* pSocket, CMessage* pMessage, CControl* pControl)
	{
		CMessage* pSendMsg = new CMessage();

switch (pMessage->m_type)
{
	 case MSG_LOGIN:
	{
		//获取到所有的用户列表。
CPtrList bodies;
pControl->getPbodies(bodies);
	//设置用户名和密码，并且产生ID给客户端。
		CBody* pBody = new CBody();
CString name = pMessage->m_text.Left(pMessage->m_text.Find(","));
pMessage->m_text.Delete(0, name.GetLength()+1);
	CString password = pMessage->m_text;
	
	//比对在线列表中是否有重名的，如果有，返回给客户端。
	if (pBody->login(name, password))
{
	//登陆成功，先将生成好的用户对象放入套接字对象。
	pSocket->setBody(pBody);
	
	//发送给客户端登陆成功的消息。
	pSendMsg->m_type = MSG_LOGIN_OK;
	pSendMsg->m_from = FROM_SYSTEM;
	pSendMsg->m_to = 1000;
	pSendMsg->m_text.Format("%d,%s,%s", 1000, pBody->getName(), pBody->getPassword());

	pControl->sendMessage(pSocket, pSendMsg);
	}

	}
	break;
	 case MSG_CLIENT_CLOSE:
		 {
			 pControl->closeSocket(pSocket);
		 //告诉所有其他客户端，当前客户端离开！
		 pSendMsg->m_type = MSG_CLIENT_CLOSE;
		 pSendMsg->m_from = FROM_SYSTEM;
		 pSendMsg->m_to = pMessage->m_from;
		 pSendMsg->m_text = pMessage->m_text;
pControl->sendMessage(pSockets, pSendMsg);
		 }
		 break;
	 default:
		 break;
}
if (NULL != pSendMsg)
	delete pSendMsg;
pSendMsg = NULL;
//end_data_come
	}

