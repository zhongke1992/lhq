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
	* 当有请求传入此链。
	* @param pSockets 桌面玩家套接字列表
	* @param pSocket 接收到消息的客户端套接字
	* @param pMessage 接收到的消息结构体
	* @param pControl 上层控制接口
	* @return void
	*/
	void CMessageChain::request(CMessage* pMessage, const CControl* pControl)
	{
	if (pMessage->m_type >= m_min && pMessage->m_type <= m_max)
		dataCome(pMessage, pControl);
	else
	{
	if (NULL == m_next)
	{
		//如果createNextInstance返回NULL，说明已经到了链的结尾，故此请求返回，不作处理。
		m_next = createNextInstance();
		if (NULL == m_next)
		return;
	}//m_next==null
	//继续往下传递请求。
	m_next->request(pMessage, pControl);
	}//else
	}

		/**
	当客服端发来数据处理
	* @param pSockets 桌面玩家套接字列表
	* @param pSocket 接收到消息的客户端套接字
	* @param pMessage 接收到的消息结构体
	* @param pControl 上层控制接口
		* @return void
	*/
void CMessageChain::dataCome(CMessage* pMessage, const CControl* pControl)
	{
	}

	/**
	* 产生子链实例。
	* @param
	* @return
	*/
	CMessageChain* CMessageChain::createNextInstance()
	{
	return NULL;
	}