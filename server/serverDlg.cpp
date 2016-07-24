// serverDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "server.h"
#include "serverDlg.h"
#include "Control.h"
#include "Body.h"
#include "SystemMessageDeal.h"

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
	: CDialog(CserverDlg::IDD, pParent),
	CMessageChain(0, 0)//由于此处只是信息处理链的开始，不做消息处理，故此消息处理的最大和最小都写0.
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
//额外的初始化代码
m_pListeningSocket = NULL;
}

CserverDlg::~CserverDlg(void)
{
	if (NULL != m_pListeningSocket) 
	delete m_pListeningSocket;
	m_pListeningSocket = NULL;
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
	
	//初始化控制接口CControl。
		CControl::getInstance()->setDlg(this);
		//pControl->setDlg(this);
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
	CControl* pControl = CControl::getInstance();

	//穿入消息处理链
request(&m_connectionList, pSocket, &pMsg, pControl);
}

	/**
	* 产生子链实例。
	* @param
	* @return
	*/
	CMessageChain* CserverDlg::createNextInstance()
	{
	return new CSystemMessageDeal(1, 100);
	}

	void CserverDlg::OnOK()
	{
		// TODO: 在此添加专用代码和/或调用基类
		if (IDYES == ::MessageBox(m_hWnd, "确定要关闭服务器吗？", "询问", MB_YESNO))
		{
		CloseServer();
			__super::OnOK();
		}
	}

	void CserverDlg::OnCancel()
	{
		// TODO: 在此添加专用代码和/或调用基类
		if (IDYES == ::MessageBox(m_hWnd, "确定要关闭服务器吗？", "询问", MB_YESNO))
		{
		CloseServer();
			__super::OnCancel();
		}
	}

	//当服务器即将关闭的时候用以清空所有资源。
	void CserverDlg::CloseServer(void)
	{
	if (NULL != m_pListeningSocket)
		delete m_pListeningSocket;
	m_pListeningSocket = NULL;

	CMessage* pMessage = new CMessage();
	while(!m_connectionList.IsEmpty())
	{
	CClientSocket* pSocket = (CClientSocket*)m_connectionList.RemoveHead();
	if (NULL == pSocket) 
		continue;
	if (NULL == pMessage)
		break;

	pMessage->m_type = MSG_SERVER_CLOSE;
	pMessage->m_from = TO_SYSTEM;
	//CBody* pBody = pSocket->getBody();	
	pMessage->m_to = 10000;
	pMessage->m_text = "服务器已关闭！";

	SendMsg(pSocket, pMessage);
	}//while
	}

	/**
	* 关闭某个客户端套接字。
	* @param pSocket 要关闭的套接字。
	* @return void
	*/
	void CserverDlg::CloseSocket(CClientSocket* pSocket)
	{
		pSocket->Close();

POSITION pos, temp;
for (pos=m_connectionList.GetHeadPosition();pos!=NULL;)
{
temp = pos;
CClientSocket* pSock = (CClientSocket*)m_connectionList.GetNext(pos);
if (pSock == pSocket)
{
m_connectionList.RemoveAt(temp);
break;
}//if
}//for
	}

	/**
	服务器像客户端发送消息
	* @param pSocket 发送消息的套接字。
	* @param pMessage 要发送的消息。
	* @return void
	*/
	void CserverDlg::SendMsg(CClientSocket* pSocket, CMessage* pMessage)
	{
		TRY
	{
		pSocket->SendMsg(pMessage);
	}
	CATCH(CFileException, e)
	{
		pSocket->Abort();
	}
	END_CATCH
	}

