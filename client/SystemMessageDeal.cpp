#include "stdafx.h"
#include "SystemMessageDeal.h"
#include "../include/message/Message.h"


CSystemMessageDeal::CSystemMessageDeal(unsigned int min, unsigned int max)
	:CMessageChain(min, max)
{
}


CSystemMessageDeal::~CSystemMessageDeal(void)
{
}

		/**
	当服务器发来数据处理
	* @param pMessage 接收到的消息结构体
	* @param pControl 上层控制接口
		* @return void
	*/
	void CSystemMessageDeal::dataCome(CMessage* pMessage, CControl* pControl)
	{
	CMessage* pSendMessage = new CMessage();

	switch(pMessage->m_type)
	{
	case MSG_LOGIN_OK:
AfxMessageBox(pMessage->m_text);	
		break;
	case MSG_SERVER_CLOSE:
		AfxMessageBox("服务器");
		break;
	default:
		break;
	}
	
	//end
	}
