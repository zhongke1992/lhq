#include "stdafx.h"
#include "SystemMessageDeal.h"
#include "../include/message/Message.h"
#include "ClientSocket.h"
#include "Control.h"
#include "Body.h"


CSystemMessageDeal::CSystemMessageDeal(void)
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
	void CSystemMessageDeal::dataCome(CPtrList* pSockets, CClientSocket* pSocket, CMessage* pMessage, const CControl* pControl)
	{
switch (pMessage->m_type)
{
case MSG_LOGIN:
	{
	//设置用户名和密码，并且产生ID给客户端。
CBody* body = new CBody();
CString name = pMessage->m_text.Left(pMessage->m_text.Find(","));
pMessage->m_text.Delete(0, name.GetLength()+1);
CString password = pMessage->m_text;
if (body->login(name, password))
{
}
	}
	break;
}
//end_data_come
	}

