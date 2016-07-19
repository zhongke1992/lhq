// Login.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "client.h"
#include "Login.h"
#include "clientDlg.h"


// CLogin �Ի���

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


// CLogin ��Ϣ�������

void CLogin::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
UpdateData();

//�ж��û����༭���Ƿ�������
if ("" == m_name)
{
MessageBox("�û�������Ϊ��!", "��ʾ");
return;
}

//�ж�����༭����Ϊ�ա�
if ("" == m_password)
{
MessageBox("���벻��Ϊ��!", "��ʾ!");
return;
}

//����CclientDlg�۵�ConnectServer���������ӷ�������
m_pDlg->ConnectServer(m_name, m_password, m_save);
	OnOK();
}
