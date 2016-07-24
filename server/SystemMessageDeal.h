#pragma once
#include "MessageChain.h"

/*
此类是为了处理系统的各种消息
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
	当客服端发来数据处理
	* @param pSockets 桌面玩家套接字列表
	* @param pSocket 发送来消息的客户端套接字
	* @param pMessage 发送的消息结构体
	* @param pControl 上层控制接口
	*/
	void dataCome(CPtrList* pSockets, CClientSocket* pSocket, CMessage* pMessage, CControl* pControl);
};

