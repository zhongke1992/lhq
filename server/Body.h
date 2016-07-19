#pragma once

/*
玩家信息类。
*/

class CBody
{
public:
	CBody(void);
	~CBody(void);

private:
	//玩家的ID
	unsigned int m_id;
	//玩家的昵称
	CString m_name;
	//玩家的密码
	CString m_password;

public:
	/**
	* 玩家登陆时确定能否登陆。
	* @param name 玩家昵称.
	* @param password 玩家密码。
	* @return 成功返回true，否则false。
	*/
		bool login(CString name, CString password);
		inline unsigned int getID() { return m_id; }
		inline CString getName() { return m_name; }
		inline CString getPassword() { return m_password; }
};

