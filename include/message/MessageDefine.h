#pragma once

/*
������Ϣ�ĺ춨�塣
�˴�Լ����
С��100��λϵͳ��Ϣ��
*/

#define MSG_VOID 0//����Ϣ
#define MSG_LOGIN 1//��½
#define MSG_SERVER_CLOSE 2//���������ر�ʱ�����ͻ��ˡ�
#define MSG_LOGIN_OK 3//���ͻ������ӷ�����ʱ�����������߿ͻ��˵�½�ɹ���
#define MSG_CLIENT_CLOSE 4//�ͻ��˸��߷������Լ��Ѿ��رա�
#define MSG_LOGIN_FAILURE 5//���������߿ͻ��ˣ�ע��ʧ�ܣ�m_text�м�¼�˴�����Ϣ��

/*
����m_from��m_to�ĺ궨��
*/
#define FROM_NONE -1//δ֪ID����Ҫϵͳ����ID��
#define TO_SYSTEM 10000//ϵͳ��ID
#define FROM_SYSTEM 10000//ϵͳ��ID
#define TO_ALL 9999//���͸�������

//������Ϣ��Χ�ĺ궨��
#define RINGE_NONE 0//���岻������Ϣ�ĺ졣
#define RINGE_SYSTEM_MIN 1//ϵͳ��Ϣ�����ܴ������С��ϢID��
#define RINGE_SYSTEM_MAX 100//ϵͳ��Ϣ�����ܴ���������Ϣid��

