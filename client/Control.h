#pragma once

/*
为了客户端逻辑类控制上层建立控制类。
此类是一个单利类，只能通过getInstance获取到使用指针。
*/

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



public:
	//工友方法
	static CControl* getInstance();

};

