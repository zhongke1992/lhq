#pragma once

/*
�����Ϣ�ࡣ
*/

class CBody
{
public:
	CBody(void);
	~CBody(void);

private:
	//��ҵ�ID
	unsigned int m_id;
	//��ҵ��ǳ�
	CString m_name;
	//��ҵ�����
	CString m_password;

public:
	/**
	* ��ҵ�½ʱȷ���ܷ��½��
	* @param name ����ǳ�.
	* @param password ������롣
	* @return �ɹ�����true������false��
	*/
		bool login(CString name, CString password);
		inline unsigned int getID() { return m_id; }
		inline CString getName() { return m_name; }
		inline CString getPassword() { return m_password; }
};

