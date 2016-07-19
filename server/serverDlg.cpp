// serverDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "server.h"
#include "serverDlg.h"

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


// CserverDlg 对话框




CserverDlg::CserverDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CserverDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
//额外的初始化代码
m_pListeningSocket = NULL;
}

CserverDlg::~CserverDlg(void)
{
	if (NULL != m_pListeningSocket) {
	delete m_pListeningSocket;
	m_pListeningSocket = NULL;
	}
}

void CserverDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CserverDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CserverDlg 消息处理程序

BOOL CserverDlg::OnInitDialog()
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

	//打开监听套接字，监听客户连接请求。
	m_pListeningSocket = new CListeningSocket(this);
	if (m_pListeningSocket->Create(8000)) {
		if (m_pListeningSocket->Listen()) {
			MessageBox("监听成功！", "恭喜");
			return true;
		}
	}
	else
	{
		CDialog::OnCancel();
	}
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CserverDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CserverDlg::OnPaint()
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
HCURSOR CserverDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//当客户要连接服务器时条用。
void CserverDlg::ProcessPendingAccept()
{
CClientSocket *pSocket = new CClientSocket(this);

if (m_pListeningSocket->Accept(*pSocket))
{
	pSocket->init();
m_connectionList.AddTail(pSocket);
}
else//没有连接成功。
delete pSocket;
}

/* *
* 当某个客户端套接字接收到数据包时调用。
* @ param pSocket 客户端套接字
*/
void CserverDlg::ProcessPendingRead(CClientSocket* pSocket)
{
	static CMessage pMessage;
	CArchive* pArIn;

//获取套接字的CArchive对象。
pArIn = pSocket->GetIn();

	//给的套接字不能为空。
	if (NULL != pSocket) {
		do {
			TRY
			{
pSocket->ReceiveMsg(&pMessage);
DataCome(pSocket, pMessage);
			}
CATCH(CFileException, e)
{
}
END_CATCH

				}
while(!pArIn->IsBufferEmpty());
	}//套接字不为空
}

/**
* 客户端数据到达处理。
* @param pSocket 客户端套接字。
* @param pMessage 发来的消息。
*/
void CserverDlg::DataCome(CClientSocket* pSocket, CMessage& pMsg)
{
switch (pMsg.m_type)
{
case MSG_LOGIN:
	MessageBox(pMsg.m_text);
	break;
}

}
