// serverDlg.cpp : ʵ���ļ�
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


// CserverDlg �Ի���




CserverDlg::CserverDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CserverDlg::IDD, pParent),
	CMessageChain(0, 0)//���ڴ˴�ֻ����Ϣ�������Ŀ�ʼ��������Ϣ�����ʴ���Ϣ�����������С��д0.
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
//����ĳ�ʼ������
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


// CserverDlg ��Ϣ�������

BOOL CserverDlg::OnInitDialog()
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

	//�򿪼����׽��֣������ͻ���������
	m_pListeningSocket = new CListeningSocket(this);
	if (m_pListeningSocket->Create(8000)) {
		if (m_pListeningSocket->Listen()) {
			MessageBox("�����ɹ���", "��ϲ");
			return true;
		}
	}
	else
	{
		CDialog::OnCancel();
	}
	
	//��ʼ�����ƽӿ�CControl��
		CControl::getInstance()->setDlg(this);
		//pControl->setDlg(this);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CserverDlg::OnPaint()
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
HCURSOR CserverDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//���ͻ�Ҫ���ӷ�����ʱ���á�
void CserverDlg::ProcessPendingAccept()
{
CClientSocket *pSocket = new CClientSocket(this);

if (m_pListeningSocket->Accept(*pSocket))
{
	pSocket->init();
m_connectionList.AddTail(pSocket);
}
else//û�����ӳɹ���
delete pSocket;
}

/* *
* ��ĳ���ͻ����׽��ֽ��յ����ݰ�ʱ���á�
* @ param pSocket �ͻ����׽���
*/
void CserverDlg::ProcessPendingRead(CClientSocket* pSocket)
{
	static CMessage pMessage;
	CArchive* pArIn;

//��ȡ�׽��ֵ�CArchive����
pArIn = pSocket->GetIn();

	//�����׽��ֲ���Ϊ�ա�
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
	}//�׽��ֲ�Ϊ��
}

/**
* �ͻ������ݵ��ﴦ��
* @param pSocket �ͻ����׽��֡�
* @param pMessage ��������Ϣ��
*/
void CserverDlg::DataCome(CClientSocket* pSocket, CMessage& pMsg)
{
	CControl* pControl = CControl::getInstance();

	//������Ϣ������
request(&m_connectionList, pSocket, &pMsg, pControl);
}

	/**
	* ��������ʵ����
	* @param
	* @return
	*/
	CMessageChain* CserverDlg::createNextInstance()
	{
	return new CSystemMessageDeal(1, 100);
	}

	void CserverDlg::OnOK()
	{
		// TODO: �ڴ����ר�ô����/����û���
		if (IDYES == ::MessageBox(m_hWnd, "ȷ��Ҫ�رշ�������", "ѯ��", MB_YESNO))
		{
		CloseServer();
			__super::OnOK();
		}
	}

	void CserverDlg::OnCancel()
	{
		// TODO: �ڴ����ר�ô����/����û���
		if (IDYES == ::MessageBox(m_hWnd, "ȷ��Ҫ�رշ�������", "ѯ��", MB_YESNO))
		{
		CloseServer();
			__super::OnCancel();
		}
	}

	//�������������رյ�ʱ���������������Դ��
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
	pMessage->m_text = "�������ѹرգ�";

	SendMsg(pSocket, pMessage);
	}//while
	}

	/**
	* �ر�ĳ���ͻ����׽��֡�
	* @param pSocket Ҫ�رյ��׽��֡�
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
	��������ͻ��˷�����Ϣ
	* @param pSocket ������Ϣ���׽��֡�
	* @param pMessage Ҫ���͵���Ϣ��
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

