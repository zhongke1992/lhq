#pragma once

/*
为了客户端逻辑类控制上层建立控制类。
此类是一个单利类，只能通过getInstance获取到使用指针。
*/

class CclientDlg;

class CControl
{
private:
	CControl(void);
		class CGarbo   //它的唯一工作就是在析构函数中删除CControl的实例
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
	//成员变量
	//系统保存的唯一的本类的实例。
static CControl* m_pControl;
//保存的主对话框的指针，用以控制各种窗口动作。
CclientDlg* m_pDlg;



public:
	//工友方法
	static CControl* getInstance();

//公开方法
public:
	inline void setDlg(CclientDlg* pDlg) { m_pDlg = pDlg; }
		/**
用于下层控制关闭通讯套接字。
* @param void
* @return void
*/
void closeSocket();

/**
下层调用，用于弹出对话框。
* @param szText 对话框的文本
* @param szTitle 对话框的标题。
* @param type 产生的对话框类型。
* @return 对话框返回的用户操作的结果。
*/
int messageBox(CString szText, CString szTitle = "", int type = 0);
};

