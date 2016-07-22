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
	* 玩家登陆时确定能否登陆。
	* @param name 玩家昵称.
	* @param password 玩家密码。
	* @return 成功返回true，否则false。
	*/
		bool CBody::login(CString name, CString password)
		{
		m_name = name;
		m_password = password;
			return true;
		}