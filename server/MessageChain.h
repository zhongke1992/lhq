#pragma once

class CClientSocket;
class CMessage;
class CControl;

class CMessageChain
{
public:
	CMessageChain(unsigned int min, unsigned int max);
	~CMessageChain(void);

private:
	//指向后续处理链的指针。
	CMessageChain* m_next;
	//该类s所能处理的最小的消息ID。
	unsigned int m_min;
	//该类所能处理的最大的消息ID。
	unsigned int m_max;

public:
	/**
	* 当有请求传入此链。
	* @param pSockets 桌面玩家套接字列表
	* @param pSocket 接收到消息的客户端套接字
	* @param pMessage 接收到的消息结构体
	* @param pControl 上层控制接口
	* @return void
	*/
	void request(CPtrList* pSockets, CClientSocket* pSocket, CMessage* pMessage, const CControl* pControl);

	/**
	* 产生子链实例。
	* @param
	* @return
	*/
	virtual CMessageChain* createNextInstance();

	/**
	当客服端发来数据处理
	* @param pSockets 桌面玩家套接字列表
	* @param pSocket 接收到消息的客户端套接字
	* @param pMessage 接收到的消息结构体
	* @param pControl 上层控制接口
		* @return void
	*/
	virtual void dataCome(CPtrList* pSockets, CClientSocket* pSocket, CMessage* pMessage, const CControl* pControl);
};

