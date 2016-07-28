#pragma once

/*
+为了服务器逻辑类控制上层建立控制类。
此类是一个单利类，只能通过getInstance获取到使用指针。
*/

class CserverDlg;
class CClientSocket;
class CMessage;

class CControl
{
private:
	CControl(void);
		class CGarbo   //它的唯一工作就是在析构函数中删除CControl的实例
		{
		public:
			~CGarbo()
			{
			if (NULL != CControl::m_pControl)
			{
			delete CControl::m_pControl;
			CControl::m_pControl = NULL;
			}
			}
		};
		static CGarbo ganbo;
public:
	virtual ~CControl(void);

private:
	//成员变量
	//系统保存的唯一的本类的实例。
static CControl* m_pControl;
//主对话框实例。
CserverDlg* m_pDlg;

public:
	//工友方法
	static CControl* getInstance();
	inline void setDlg(CserverDlg* pDlg) { m_pDlg = pDlg; }
	
	/**
	* 获取到所有套接字中的CBody对象的指针。
	* @param pBodies 用来获取指针的容器。
	* @return void.
	*/
	void getPbodies(CPtrList& pBodies);
	
	/**
	发送消息给某个客户端。
	* @param pSocket 要发送到的消息结构体。
	* @param pMessage 发送的消息。
	* @retgurn void
	*/
	void sendMessage(CClientSocket* pSocket, CMessage* pMessage);

	/**
	关闭某客户端套接字
* @param pSocket 要关闭的客户端套接字。
* @return void
*/
	void closeSocket(CClientSocket* pSocket);

	/**
	发送消息给一组人。
	* @param pSockets 要发送给的人的列表。
	* @param pMessage 要发送的消息。
* @return void
*/
	void sendMessage(CPtrList* pSockets, CMessage* pMessage);
};

