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
	���������������ݴ���
	* @param pMessage ���յ�����Ϣ�ṹ��
	* @param pControl �ϲ���ƽӿ�
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
		AfxMessageBox("������");
		break;
	default:
		break;
	}
	
	//end
	}
