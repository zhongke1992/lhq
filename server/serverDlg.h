// serverDlg.h : ͷ�ļ�
//

#pragma once

#include "ListeningSocket.h"
#include "ClientSocket.h"
#include "../include/message/Message.h"
#include "SystemMessageDeal.h"
#include "MessageChain.h"

// CserverDlg �Ի���
class CserverDlg : public CDialog, public CMessageChain
{
// ����
public:
	CserverDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CserverDlg(void);

// �Ի�������
	enum { IDD = IDD_SERVER_DIALOG };

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

private:
	//�����׽���
	CListeningSocket *m_pListeningSocket;
	//�ͻ������׽����б�
CPtrList m_connectionList;
//������Ϣ��
void DataCome(CClientSocket* pSocket, CMessage& pMsg);

public:
//���ͻ�Ҫ���ӷ�����ʱ���á�
	void ProcessPendingAccept();
	//���ͻ�������Ϣ��ʱ������
	void ProcessPendingRead(CClientSocket* pSocket);

		/**
	* ��������ʵ����
	* @param
	* @return
	*/
	virtual CMessageChain* createNextInstance();
	virtual void OnOK();
	virtual void OnCancel();
private:
	//�������������رյ�ʱ�����.
	void CloseServer(void);

	/**
	* �ر�ĳ���ͻ����׽��֡�
	* @param pSocket Ҫ�رյ��׽��֡�
	* @return void
	*/
	void CserverDlg::CloseSocket(CClientSocket* pSocket);

	/**
	��������ͻ��˷�����Ϣ
	* @param pSocket ������Ϣ���׽��֡�
	* @param pMessage Ҫ���͵���Ϣ��
	* @return void
	*/
	void SendMsg(CClientSocket* pSocket, CMessage* pMessage);
};
