#pragma once

/*
+Ϊ�˷������߼�������ϲ㽨�������ࡣ
������һ�������ֻ࣬��ͨ��getInstance��ȡ��ʹ��ָ�롣
*/

class CserverDlg;
class CClientSocket;
class CMessage;

class CControl
{
private:
	CControl(void);
		class CGarbo   //����Ψһ��������������������ɾ��CControl��ʵ��
		{
		public:
			~CGarbo()
			{
			if (NULL != CControl::m_pControl)
			{
			delete CControl::m_pControl;
			CControl::m_pControl = NULL;
			}
			}
		};
		static CGarbo ganbo;
public:
	virtual ~CControl(void);

private:
	//��Ա����
	//ϵͳ�����Ψһ�ı����ʵ����
static CControl* m_pControl;
//���Ի���ʵ����
CserverDlg* m_pDlg;

public:
	//���ѷ���
	static CControl* getInstance();
	inline void setDlg(CserverDlg* pDlg) { m_pDlg = pDlg; }
	
	/**
	* ��ȡ�������׽����е�CBody�����ָ�롣
	* @param pBodies ������ȡָ���������
	* @return void.
	*/
	void getPbodies(CPtrList& pBodies);
	
	/**
	������Ϣ��ĳ���ͻ��ˡ�
	* @param pSocket Ҫ���͵�����Ϣ�ṹ�塣
	* @param pMessage ���͵���Ϣ��
	* @retgurn void
	*/
	void sendMessage(CClientSocket* pSocket, CMessage* pMessage);

	/**
	�ر�ĳ�ͻ����׽���
* @param pSocket Ҫ�رյĿͻ����׽��֡�
* @return void
*/
	void closeSocket(CClientSocket* pSocket);

	/**
	������Ϣ��һ���ˡ�
	* @param pSockets Ҫ���͸����˵��б�
	* @param pMessage Ҫ���͵���Ϣ��
* @return void
*/
	void sendMessage(CPtrList* pSockets, CMessage* pMessage);
};

