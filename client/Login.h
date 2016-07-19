#pragma once


// CLogin 对话框

class CclientDlg;

class CLogin : public CDialog
{
	DECLARE_DYNAMIC(CLogin)

public:
	CLogin(CclientDlg* pDlg, CWnd* pParent = NULL);   // 标准构造函数
		virtual ~CLogin();

// 对话框数据
	enum { IDD = IDD_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
