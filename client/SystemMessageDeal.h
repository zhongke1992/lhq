#pragma once
#include "messagechain.h"

class CSystemMessageDeal :
	public CMessageChain
{
public:
	CSystemMessageDeal(unsigned int min, unsigned int max);
	virtual ~CSystemMessageDeal(void);

		/**
	���������������ݴ���
	* @param pMessage ���յ�����Ϣ�ṹ��
	* @param pControl �ϲ���ƽӿ�
		* @return void
	*/
	virtual void dataCome(CMessage* pMessage, CControl* pControl);
		};

