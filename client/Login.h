#pragma once


// CLogin �Ի���

class CclientDlg;

class CLogin : public CDialog
{
	DECLARE_DYNAMIC(CLogin)

public:
	CLogin(CclientDlg* pDlg, CWnd* pParent = NULL);   // ��׼���캯��
		virtual ~CLogin();

// �Ի�������
	enum { IDD = IDD_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	CclientDlg* m_pDlg;
	CString m_name;
	CString m_password;
public:
	afx_msg void OnBnClickedOk();
private:
	BOOL m_save;
};
