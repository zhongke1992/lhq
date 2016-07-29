#pragma once

/*
所有消息的红定义。
此处约定：
小于100的位系统消息。
*/

#define MSG_VOID 0//空消息
#define MSG_LOGIN 1//登陆
#define MSG_SERVER_CLOSE 2//当服务器关闭时发给客户端。
#define MSG_LOGIN_OK 3//当客户端连接服务器时，服务器告诉客户端登陆成功。
#define MSG_CLIENT_CLOSE 4//客户端告诉服务器自己已经关闭。
#define MSG_LOGIN_FAILURE 5//服务器告诉客户端，注册失败，m_text中记录了错误信息。

/*
关于m_from和m_to的宏定义
*/
#define FROM_NONE -1//未知ID，需要系统分配ID。
#define TO_SYSTEM 10000//系统的ID
#define FROM_SYSTEM 10000//系统的ID
#define TO_ALL 9999//发送给所有人

//关于消息范围的宏定义
#define RINGE_NONE 0//定义不处理消息的红。
#define RINGE_SYSTEM_MIN 1//系统消息类所能处理的最小消息ID。
#define RINGE_SYSTEM_MAX 100//系统消息类所能处理的最大消息id。

