// clientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "client.h"
#include "clientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CclientDlg 对话框




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


// CclientDlg 消息处理程序

BOOL CclientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	if (NULL != m_pLogin)
	{
delete m_pLogin;
		m_pLogin = NULL;
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CclientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CclientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CclientDlg::OnLogin()
{
	// TODO: 在此添加命令处理程序代码
	if (NULL == m_pLogin)
m_pLogin = new CLogin(this);

	m_pLogin->DoModal();
}

void CclientDlg::ConnectServer(const CString name, const CString password, bool save)
{
	//初始化套接字库。
	if (!AfxSocketInit())
	{
		AfxMessageBox("初始化失败");
		return;
	}

//如果已经和服务器进行了连接，则不需要重新建立。
	if (m_bConnected)
return;

	//建立套接字对象
	if (NULL == m_pSocket) {
	m_pSocket = new CClientSocket(this);
if (NULL == m_pSocket)
return;
	}

//初始化套接字对象
	if (!m_pSocket->Create())
{
delete m_pSocket;
m_pSocket = NULL;
MessageBox("建立套接字出错！", "提示");
return ;
}

//连接服务器
while(!m_pSocket->Connect("127.0.0.1", 8000))
{
if (IDNO == AfxMessageBox("连接服务器失败，是否需要重新尝试？", MB_YESNO))
{
delete m_pSocket;
m_pSocket = NULL;
return;
}
}

//初始化CClientSocket。
m_pSocket->init();

m_bConnected = true;

//将登陆菜单项设置成不可用。
CMenu* pMenu = GetMenu();
CMenu* pSubMenu = pMenu->GetSubMenu(0);
pSubMenu->EnableMenuItem(0, MF_BYPOSITION | MF_DISABLED | MF_GRAYED);

//发送登陆消息
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

