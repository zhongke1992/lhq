// Login.cpp : 实现文件
//

#include "stdafx.h"
#include "client.h"
#include "Login.h"
#include "clientDlg.h"


// CLogin 对话框

IMPLEMENT_DYNAMIC(CLogin, CDialog)

CLogin::CLogin(CclientDlg* pDlg, CWnd* pParent /*=NULL*/)
	: CDialog(CLogin::IDD, pParent)
	, m_name(_T(""))
	, m_password(_T(""))
	, m_save(FALSE)
{
m_pDlg = pDlg;
}

CLogin::~CLogin()
{
}

void CLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_NAME, m_name);
	DDV_MaxChars(pDX, m_name, 20);
	DDX_Text(pDX, IDC_PASSWORD, m_password);
	DDV_MaxChars(pDX, m_password, 20);
	DDX_Check(pDX, IDC_CHECK1, m_save);
}


BEGIN_MESSAGE_MAP(CLogin, CDialog)
	ON_BN_CLICKED(IDOK, &CLogin::OnBnClickedOk)
END_MESSAGE_MAP()


// CLogin 消息处理程序

void CLogin::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
UpdateData();

//判断用户名编辑框是否有内容
if ("" == m_name)
{
MessageBox("用户名不能为空!", "提示");
return;
}

//判断密码编辑框不能为空。
if ("" == m_password)
{
MessageBox("密码不能为空!", "提示!");
return;
}

//调用CclientDlg累的ConnectServer函数，连接服务器。
m_pDlg->ConnectServer(m_name, m_password, m_save);
	OnOK();
}
