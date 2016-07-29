#include "stdafx.h"
#include "MessageChain.h"
#include "../include/message/Message.h"


CMessageChain::CMessageChain(unsigned int min, unsigned int max)
{
m_min = min;
m_max = max;
m_next = NULL;
}


CMessageChain::~CMessageChain(void)
{
if (NULL != m_next)
	delete m_next;
m_next = NULL;
}

	/**
	* ���������������
	* @param pSockets ��������׽����б�
	* @param pSocket ���յ���Ϣ�Ŀͻ����׽���
	* @param pMessage ���յ�����Ϣ�ṹ��
	* @param pControl �ϲ���ƽӿ�
	* @return void
	*/
	void CMessageChain::request(vector<CClientSocket*>* pSockets, CClientSocket* pSocket, CMessage* pMessage, CControl* pControl)
	{
	if (pMessage->m_type >= m_min && pMessage->m_type <= m_max)
		dataCome(pSockets, pSocket, pMessage, pControl);
	else
	{
	if (NULL == m_next)
	{
		//���createNextInstance����NULL��˵���Ѿ��������Ľ�β���ʴ����󷵻أ���������
if (NULL == (m_next = createNextInstance()))
		return;
	}//m_next==null
	//�������´�������
	m_next->request(pSockets, pSocket, pMessage, pControl);
	}//else
	}

		/**
	���ͷ��˷������ݴ���
	* @param pSockets ��������׽����б�
	* @param pSocket ���յ���Ϣ�Ŀͻ����׽���
	* @param pMessage ���յ�����Ϣ�ṹ��
	* @param pControl �ϲ���ƽӿ�
		* @return void
	*/
void CMessageChain::dataCome(vector<CClientSocket*>* pSockets, CClientSocket* pSocket, CMessage* pMessage, CControl* pControl)
	{
	}

	/**
	* ��������ʵ����
	* @param
	* @return
	*/
	CMessageChain* CMessageChain::createNextInstance()
	{
	return NULL;
	}