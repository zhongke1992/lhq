#pragma once
#include "afx.h"
#include "MessageDefine.h"
/*
* 所有消息的鸡肋
*/

//set函数红
#define SET_M_TYPE 0//设置m_type的值
#define SET_M_TEXT 1//设置m_text的值

class CMessage :
	public CObject
{
public:
	CMessage(void);
	~CMessage(void);

public:
void Serialize(CArchive& ar);
//清零
void Reset();

//消息编号。
	int m_type;
	//消息发送方ID
	int m_from;
	//消息接收方ID。
	int m_to;
	//消息附加文本信息
	CString m_text;
};

