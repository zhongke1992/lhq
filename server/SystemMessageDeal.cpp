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
	���ͷ��˷������ݴ���
	* @param pSockets ��������׽����б�
	* @param pSocket ��������Ϣ�Ŀͻ����׽���
	* @param pMessage ���͵���Ϣ�ṹ��
	* @param pControl �ϲ���ƽӿ�
	*/
	void CSystemMessageDeal::dataCome(CPtrList* pSockets, CClientSocket* pSocket, CMessage* pMessage, const CControl* pControl)
	{
switch (pMessage->m_type)
{
case MSG_LOGIN:
	{
	//�����û��������룬���Ҳ���ID���ͻ��ˡ�
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

