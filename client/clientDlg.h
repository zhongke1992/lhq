// clientDlg.h : 头文件
//

#pragma once

#include "Login.h"
#include "ClientSocket.h"
#include "../include/message/MessageDefine.h"
#include "../include/message/Message.h"
#include "MessageChain.h"

// CclientDlg 对话框
class CclientDlg : public CDialog, public CMessageChain
{
// 构造
public:
	CclientDlg(CWnd* pParent = NULL);	// 标准构造函数
	virtual ~CclientDlg(void);

// 对话框数据
	enum { IDD = IDD_CLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnLogin();

private:
	//登陆对话框
CLogin* m_pLogin;
//表示是否建立了连接
bool m_bConnected;
//连接套接字对象
CClientSocket* m_pSocket;

public:
	//连接服务器函数，前两个参数是用户名和密码，最后一个参数是是否保存用户名密码。
	void ConnectServer(const CString name, const CString password, bool save);
void SendMsg(CMessage* pMsg);
//当套接字接收到消息的时候调用，用以接收客户端发来的消息。
void ProcessPendingRead();

	/**
	* 产生子链实例。
	* @param
	* @return
	*/
	virtual CMessageChain* createNextInstance();
};
