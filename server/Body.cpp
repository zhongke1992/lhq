#include "stdafx.h"
#include "Body.h"


CBody::CBody(void)
{
m_id = 0;
m_name = "";
m_password = "";
}

CBody::~CBody(void)
{
}

/**
	* ��ҵ�½ʱȷ���ܷ��½��
	* @param name ����ǳ�.
	* @param password ������롣
	* @return �ɹ�����true������false��
	*/
		bool CBody::login(CString name, CString password)
		{
		m_name = name;
		m_password = password;
			return true;
		}