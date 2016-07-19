// clientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "client.h"
#include "clientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CclientDlg �Ի���




CclientDlg::CclientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CclientDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
m_pLogin = NULL;
m_bConnected = false;
m_pSocket = NULL;
}

CclientDlg::~CclientDlg()
{
if (NULL != m_pLogin)
{
delete m_pLogin;
m_pLogin = NULL;
}
}

void CclientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CclientDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_COMMAND(IDM_LOGIN, &CclientDlg::OnLogin)
END_MESSAGE_MAP()


// CclientDlg ��Ϣ�������

BOOL CclientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	if (NULL != m_pLogin)
	{
delete m_pLogin;
		m_pLogin = NULL;
	}

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CclientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CclientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CclientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CclientDlg::OnLogin()
{
	// TODO: �ڴ���������������
	if (NULL == m_pLogin)
m_pLogin = new CLogin(this);

	m_pLogin->DoModal();
}

void CclientDlg::ConnectServer(const CString name, const CString password, bool save)
{
	//��ʼ���׽��ֿ⡣
	if (!AfxSocketInit())
	{
		AfxMessageBox("��ʼ��ʧ��");
		return;
	}

//����Ѿ��ͷ��������������ӣ�����Ҫ���½�����
	if (m_bConnected)
return;

	//�����׽��ֶ���
	if (NULL == m_pSocket) {
	m_pSocket = new CClientSocket(this);
if (NULL == m_pSocket)
return;
	}

//��ʼ���׽��ֶ���
	if (!m_pSocket->Create())
{
delete m_pSocket;
m_pSocket = NULL;
MessageBox("�����׽��ֳ���", "��ʾ");
return ;
}

//���ӷ�����
while(!m_pSocket->Connect("127.0.0.1", 8000))
{
if (IDNO == AfxMessageBox("���ӷ�����ʧ�ܣ��Ƿ���Ҫ���³��ԣ�", MB_YESNO))
{
delete m_pSocket;
m_pSocket = NULL;
return;
}
}

//��ʼ��CClientSocket��
m_pSocket->init();

m_bConnected = true;

//����½�˵������óɲ����á�
CMenu* pMenu = GetMenu();
CMenu* pSubMenu = pMenu->GetSubMenu(0);
pSubMenu->EnableMenuItem(0, MF_BYPOSITION | MF_DISABLED | MF_GRAYED);

//���͵�½��Ϣ
CMessage* pMessage = new CMessage;
pMessage->m_type = MSG_LOGIN;
pMessage->m_from = FROM_NONE;
pMessage->m_to = TO_SYSTEM;
	pMessage->m_text = name+","+password;
SendMsg(pMessage);
}

void CclientDlg::SendMsg(CMessage* pMessage)
{
m_pSocket->SendMsg(pMessage);
}

