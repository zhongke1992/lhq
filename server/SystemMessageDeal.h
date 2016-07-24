#pragma once
#include "MessageChain.h"

/*
������Ϊ�˴���ϵͳ�ĸ�����Ϣ
*/

class CClientSocket;
class CMessage;
class CControl;

class CSystemMessageDeal : public CMessageChain
{
public:
	CSystemMessageDeal(unsigned int min, unsigned int max);
	~CSystemMessageDeal(void);

public:
	/**
	���ͷ��˷������ݴ���
	* @param pSockets ��������׽����б�
	* @param pSocket ��������Ϣ�Ŀͻ����׽���
	* @param pMessage ���͵���Ϣ�ṹ��
	* @param pControl �ϲ���ƽӿ�
	*/
	void dataCome(CPtrList* pSockets, CClientSocket* pSocket, CMessage* pMessage, CControl* pControl);
};

