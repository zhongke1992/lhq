// serverDlg.h : 头文件
//

#pragma once

#include "ListeningSocket.h"
#include "ClientSocket.h"
#include "../include/message/Message.h"
#include "SystemMessageDeal.h"

// CserverDlg 对话框
class CserverDlg : public CDialog
{
// 构造
public:
	CserverDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CserverDlg(void);

// 对话框数据
	enum { IDD = IDD_SERVER_DIALOG };

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

private:
	//监听套接字
	CListeningSocket *m_pListeningSocket;
	//客户连接套接字列表。
CPtrList m_connectionList;
//处理系统消息的累
CSystemMessageDeal m_systemMessageDeal;
//处理消息。
void DataCome(CClientSocket* pSocket, CMessage& pMsg);

public:
//当客户要连接服务器时条用。
	void ProcessPendingAccept();
	//当客户发来消息的时候条用
	void ProcessPendingRead(CClientSocket* pSocket);
};
