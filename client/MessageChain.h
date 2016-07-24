#pragma once

class CClientSocket;
class CMessage;
class CControl;

class CMessageChain
{
public:
	CMessageChain(unsigned int min, unsigned int max);
	~CMessageChain(void);

private:
	//ָ�������������ָ�롣
	CMessageChain* m_next;
	//����s���ܴ������С����ϢID��
	unsigned int m_min;
	//�������ܴ����������ϢID��
	unsigned int m_max;

public:
	/**
	* ���������������
	* @param pSockets ��������׽����б�
	* @param pSocket ���յ���Ϣ�Ŀͻ����׽���
	* @param pMessage ���յ�����Ϣ�ṹ��
	* @param pControl �ϲ���ƽӿ�
	* @return void
	*/
	void request(CMessage* pMessage, CControl* pControl);

	/**
	* ��������ʵ����
	* @param
	* @return
	*/
	virtual CMessageChain* createNextInstance();

	/**
	���������������ݴ���
	* @param pMessage ���յ�����Ϣ�ṹ��
	* @param pControl �ϲ���ƽӿ�
		* @return void
	*/
	virtual void dataCome(CMessage* pMessage, CControl* pControl);
};

