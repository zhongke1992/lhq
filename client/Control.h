#pragma once

/*
Ϊ�˿ͻ����߼�������ϲ㽨�������ࡣ
������һ�������ֻ࣬��ͨ��getInstance��ȡ��ʹ��ָ�롣
*/

class CclientDlg;

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
//��������Ի����ָ�룬���Կ��Ƹ��ִ��ڶ�����
CclientDlg* m_pDlg;



public:
	//���ѷ���
	static CControl* getInstance();

//��������
public:
	inline void setDlg(CclientDlg* pDlg) { m_pDlg = pDlg; }
		/**
�����²���ƹر�ͨѶ�׽��֡�
* @param void
* @return void
*/
void closeSocket();

/**
�²���ã����ڵ����Ի���
* @param szText �Ի�����ı�
* @param szTitle �Ի���ı��⡣
* @param type �����ĶԻ������͡�
* @return �Ի��򷵻ص��û������Ľ����
*/
int messageBox(CString szText, CString szTitle = "", int type = 0);
};

