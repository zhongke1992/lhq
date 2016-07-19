#pragma once

/*
所有消息的红定义。
此处约定：
小于100的位系统消息。
*/

#define MSG_VOID -1//空消息
#define MSG_LOGIN 1//登陆

/*
关于m_from和m_to的宏定义
*/
#define FROM_NONE -1//未知ID，需要系统分配ID。
#define TO_SYSTEM 10000//系统的ID
#define TO_ALL 9999//发送给所有人
