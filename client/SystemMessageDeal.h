#pragma once
#include "messagechain.h"

class CSystemMessageDeal :
	public CMessageChain
{
public:
	CSystemMessageDeal(unsigned int min, unsigned int max);
	virtual ~CSystemMessageDeal(void);

		/**
	当服务器发来数据处理
	* @param pMessage 接收到的消息结构体
	* @param pControl 上层控制接口
		* @return void
	*/
	virtual void dataCome(CMessage* pMessage, CControl* pControl);
		};

