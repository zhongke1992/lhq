#pragma once

/*
Ϊ�˿ͻ����߼�������ϲ㽨�������ࡣ
������һ�������ֻ࣬��ͨ��getInstance��ȡ��ʹ��ָ�롣
*/

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



public:
	//���ѷ���
	static CControl* getInstance();

};

