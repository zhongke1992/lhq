// clientDlg.h : ͷ�ļ�
//

#pragma once

#include "Login.h"
#include "ClientSocket.h"
#include "../include/message/MessageDefine.h"
#include "../include/message/Message.h"
#include "MessageChain.h"

// CclientDlg �Ի���
class CclientDlg : public CDialog, public CMessageChain
{
// ����
public:
	CclientDlg(CWnd* pParent = NULL);	// ��׼���캯��
	virtual ~CclientDlg(void);

// �Ի�������
	enum { IDD = IDD_CLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnLogin();

private:
	//��½�Ի���
CLogin* m_pLogin;
//��ʾ�Ƿ���������
bool m_bConnected;
//�����׽��ֶ���
CClientSocket* m_pSocket;

public:
	//���ӷ�����������ǰ�����������û��������룬���һ���������Ƿ񱣴��û������롣
	void ConnectServer(const CString name, const CString password, bool save);
void SendMsg(CMessage* pMsg);
//���׽��ֽ��յ���Ϣ��ʱ����ã����Խ��տͻ��˷�������Ϣ��
void ProcessPendingRead();

	/**
	* ��������ʵ����
	* @param
	* @return
	*/
	virtual CMessageChain* createNextInstance();
};
