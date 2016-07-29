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
	���ͷ��˷������ݴ���
	* @param pSockets ��������׽����б�
	* @param pSocket ��������Ϣ�Ŀͻ����׽���
	* @param pMessage ���͵���Ϣ�ṹ��
	* @param pControl �ϲ���ƽӿ�
	*/
	void CSystemMessageDeal::dataCome(vector<CClientSocket*>* pSockets, CClientSocket* pSocket, CMessage* pMessage, CControl* pControl)
	{
		CMessage* pSendMsg = new CMessage();

switch (pMessage->m_type)
{
	 case MSG_LOGIN:
	{
		//��ȡ�����е��û��б�
vector<CBody*> bodies;
pControl->getBodies(pSockets, bodies);
	//�����û��������룬���Ҳ���ID���ͻ��ˡ�
		CBody* pBody = new CBody();
CString name = pMessage->m_text.Left(pMessage->m_text.Find(","));
pMessage->m_text.Delete(0, name.GetLength()+1);
	CString password = pMessage->m_text;
	
	//�ȶ������б����Ƿ��������ģ�����У����ظ��ͻ��ˡ�
		vector<CBody*>::iterator iter;
	for (iter=bodies.begin();iter!=bodies.end();iter++)
	{
	CBody* temp = *iter;
	
	if (name == temp->getName())
	{
				//�Ƚ�������Ϣ���͸��ͻ��ˡ�
				pSendMsg->m_type = MSG_LOGIN_FAILURE;
pSendMsg->m_text = "��½ʧ�ܣ����ǳ��Ѿ�����ע����ˣ�";
pControl->sendMessage(pSocket, pSendMsg);
	
//ע��ʧ��֮�󣬹رյ�ǰ�׽���
		pControl->closeSocket(pSockets, pSocket);
		delete pBody;
	return;
	}//if
	}//for

		if (pBody->login(name, password))
{
	//��½�ɹ����Ƚ����ɺõ��û���������׽��ֶ���
	pSocket->setBody(pBody);
	
	//���͸��ͻ��˵�½�ɹ�����Ϣ��
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
			 pControl->closeSocket(pSockets, pSocket);

			 //�������������ͻ��ˣ���ǰ�ͻ����뿪��
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

