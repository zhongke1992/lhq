#pragma once
#include "afx.h"
#include "MessageDefine.h"
/*
* ������Ϣ�ļ���
*/

//set������
#define SET_M_TYPE 0//����m_type��ֵ
#define SET_M_TEXT 1//����m_text��ֵ

class CMessage :
	public CObject
{
public:
	CMessage(void);
	~CMessage(void);

public:
void Serialize(CArchive& ar);
//����
void Reset();

//��Ϣ��š�
	int m_type;
	//��Ϣ���ͷ�ID
	int m_from;
	//��Ϣ���շ�ID��
	int m_to;
	//��Ϣ�����ı���Ϣ
	CString m_text;
};

