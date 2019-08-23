/*
* CoolQ Demo for VC++ 
* Api Version 9
* Written by Coxxs & Thanks for the help of orzFly
*/

#include "stdafx.h"
#include "string"
#include "cqp.h"
#include "appmain.h" //应用AppID等信息，请正确填写，否则酷Q可能无法加载

//#include"dajiang.h"
#include<time.h>
#include<fstream>

using namespace std;

int ac = -1; //AuthCode 调用酷Q的方法时需要用到
bool enabled = false;



/* 
* 返回应用的ApiVer、Appid，打包后将不会调用
*/
CQEVENT(const char*, AppInfo, 0)() {
	return CQAPPINFO;
}


/* 
* 接收应用AuthCode，酷Q读取应用信息后，如果接受该应用，将会调用这个函数并传递AuthCode。
* 不要在本函数处理其他任何代码，以免发生异常情况。如需执行初始化代码请在Startup事件中执行（Type=1001）。
*/
CQEVENT(int32_t, Initialize, 4)(int32_t AuthCode) {
	ac = AuthCode;
	return 0;
}


/*
* Type=1001 酷Q启动
* 无论本应用是否被启用，本函数都会在酷Q启动后执行一次，请在这里执行应用初始化代码。
* 如非必要，不建议在这里加载窗口。（可以添加菜单，让用户手动打开窗口）
*/
CQEVENT(int32_t, __eventStartup, 0)() {
	return 0;
}


/*
* Type=1002 酷Q退出
* 无论本应用是否被启用，本函数都会在酷Q退出前执行一次，请在这里执行插件关闭代码。
* 本函数调用完毕后，酷Q将很快关闭，请不要再通过线程等方式执行其他代码。
*/
CQEVENT(int32_t, __eventExit, 0)() {

	return 0;
}

/*
* Type=1003 应用已被启用
* 当应用被启用后，将收到此事件。
* 如果酷Q载入时应用已被启用，则在_eventStartup(Type=1001,酷Q启动)被调用后，本函数也将被调用一次。
* 如非必要，不建议在这里加载窗口。（可以添加菜单，让用户手动打开窗口）
*/
CQEVENT(int32_t, __eventEnable, 0)() {
	enabled = true;
	return 0;
}


/*
* Type=1004 应用将被停用
* 当应用被停用前，将收到此事件。
* 如果酷Q载入时应用已被停用，则本函数*不会*被调用。
* 无论本应用是否被启用，酷Q关闭前本函数都*不会*被调用。
*/
CQEVENT(int32_t, __eventDisable, 0)() {
	enabled = false;
	return 0;
}


/*
* Type=21 私聊消息
* subType 子类型，11/来自好友 1/来自在线状态 2/来自群 3/来自讨论组
*/
CQEVENT(int32_t, __eventPrivateMsg, 24)(int32_t subType, int32_t msgId, int64_t fromQQ, const char *themsg, int32_t font) {
	string msg = themsg;
	/*string msglast;

	
	ifstream read("data.txt",ios::_Nocreate);
	if (read.fail()) { return EVENT_BLOCK; }
	read >> msglast;
	read.close();
	
	//复读
	if (msglast == msg)
	{CQ_sendPrivateMsg(ac, fromQQ, (char*)msg.c_str());msg.clear();return EVENT_BLOCK;}

	ofstream write("data.txt", ios::_Nocreate | ios::trunc);
	if (write.fail()) { return EVENT_BLOCK; }
	write << msg;
	write.close();*/

	//版本信息
	if (msg == "-help")
	{CQ_sendPrivateMsg(ac, fromQQ, "自己摸索的说");return EVENT_BLOCK;}
	if (msg == "-about")
	{CQ_sendPrivateMsg(ac, fromQQ, "version:0.0.2\nversion_id:2\nauthor:Bao Peize");return EVENT_BLOCK;}

	//问好
	if (NULL != strstr((char*)msg.c_str(), "大酱早安"))
	{CQ_sendPrivateMsg(ac, fromQQ, "おはよ");return EVENT_BLOCK;}
	else if (NULL != strstr((char*)msg.c_str(), "大酱晚安"))
	{CQ_sendPrivateMsg(ac, fromQQ, "おやすみ");return EVENT_BLOCK;}
	else if (NULL != (strstr((char*)msg.c_str(), "大酱中午好") || strstr((char*)msg.c_str(), "大酱午安")))
	{CQ_sendPrivateMsg(ac, fromQQ, "中午好鸭");return EVENT_BLOCK;}
	else if (NULL != strstr((char*)msg.c_str(), "大酱"))
	{CQ_sendPrivateMsg(ac, fromQQ, "はい");}
	else if (NULL != (strstr((char*)msg.c_str(), "社会") || strstr((char*)msg.c_str(), "可怕")))
	{CQ_sendPrivateMsg(ac, fromQQ, "社会社会[CQ:face,id=178]");return EVENT_BLOCK;}
	else if (NULL != (strstr((char*)msg.c_str(), "AMD") || strstr((char*)msg.c_str(), "amd")))
	{CQ_sendPrivateMsg(ac, fromQQ, "Intel牛逼！[CQ:face,id=178]");return EVENT_BLOCK;}
	else {}

	//复读
	if ("复读" == msg.substr(0, 4))
	{msg = msg.substr(4);CQ_sendPrivateMsg(ac, fromQQ, (char*)msg.c_str());return EVENT_BLOCK;}

	//随机选择
	if ("/随机选择" == msg.substr(0, 9))
	{
		msg.erase(0, 10);				//gb10830编码一个字符占两个字节
		int i = 0, flag = 0;			//i记录‘|’个数，flag记录‘|’下标
		for (i = -1;flag >= 0;i++)
		{
			flag = msg.find('|', flag + 1);
		}
		srand((unsigned)time(NULL));
		int choose = rand() % (i + 1);	//choose记录大酱的选择（从0开始）
		i = 0, flag = 0;				//i和flag重新初始化
		for (i = 0, flag = 0;i < choose;i++)
		{
			flag = msg.find('|', flag + 1);
		}
		msg = msg.substr(flag);
		if ('|' == msg[0])				//除去可能的前置'|'
		{
			msg = msg.substr(1);
		}
		flag = msg.find('|');			//除去可能的后置'|'
		if (-1 != flag)
		{
			msg = msg.substr(0, flag);
		}
		msg = "嗯，大酱选择了" + msg;
		msg += "的说(≧▽≦)";
		CQ_sendPrivateMsg(ac, fromQQ, (char*)msg.c_str());
		return EVENT_BLOCK;
	}

	//随机复读
	srand((unsigned)time(NULL));
	if (!(rand() % 100))
	{CQ_sendPrivateMsg(ac, fromQQ, (char*)msg.c_str());return EVENT_BLOCK;}
	

	//如果要回复消息，请调用酷Q方法发送，并且这里 return EVENT_BLOCK - 截断本条消息，不再继续处理  注意：应用优先级设置为"最高"(10000)时，不得使用本返回值
	//如果不回复消息，交由之后的应用/过滤器处理，这里 return EVENT_IGNORE - 忽略本条消息
	return EVENT_IGNORE;
}


/*
* Type=2 群消息
*/
CQEVENT(int32_t, __eventGroupMsg, 36)(int32_t subType, int32_t msgId, int64_t fromGroup, int64_t fromQQ, const char *fromAnonymous, const char *themsg, int32_t font) {
	string msg = themsg;

	//版本信息
	if (msg == "-help")
	{CQ_sendGroupMsg(ac, fromGroup, "自己摸索的说");return EVENT_BLOCK;}
	if (msg == "-about")
	{CQ_sendGroupMsg(ac, fromGroup, "version:0.0.2\nversion_id:2\nauthor:Bao Peize");return EVENT_BLOCK;}

	//禁言(迫害狗群员)
	if (fromGroup == 719120383)
	{
		if (NULL != (strstr((char*)msg.c_str(), "cxk")|| (strstr((char*)msg.c_str(), "菜") && strstr((char*)msg.c_str(), "虚") && strstr((char*)msg.c_str(), "鲲"))))
		{CQ_setGroupBan(ac,fromGroup,fromQQ,60);CQ_sendGroupMsg(ac, fromGroup, "[CQ:face,id=178]");return EVENT_BLOCK;}
		if (NULL != (strstr((char*)msg.c_str(), "esu")|| strstr((char*)msg.c_str(), "pronhub")|| strstr((char*)msg.c_str(), "SSR")|| strstr((char*)msg.c_str(), "V2Ray")))
		{CQ_setGroupBan(ac, fromGroup, fromQQ, 60);CQ_sendGroupMsg(ac, fromGroup, "[CQ:face,id=178]");return EVENT_BLOCK;}
		if (NULL != (strstr((char*)msg.c_str(), "平胸怪") || strstr((char*)msg.c_str(), "野兽先辈") || strstr((char*)msg.c_str(), "昏睡红茶") || strstr((char*)msg.c_str(), "雷普")))
		{CQ_setGroupBan(ac, fromGroup, fromQQ, 60);CQ_sendGroupMsg(ac, fromGroup, "[CQ:face,id=178]");return EVENT_BLOCK;}
		if (NULL != (strstr((char*)msg.c_str(), "比利") || strstr((char*)msg.c_str(), "哲学") || strstr((char*)msg.c_str(), "出柜")))
		{CQ_setGroupBan(ac, fromGroup, fromQQ, 60);CQ_sendGroupMsg(ac, fromGroup, "[CQ:face,id=178]");return EVENT_BLOCK;}
		//if (NULL != (strstr((char*)msg.c_str(), "南") && strstr((char*)msg.c_str(), "应")))
		//{CQ_setGroupBan(ac, fromGroup, fromQQ, 60);CQ_sendGroupMsg(ac, fromGroup, "[CQ:face,id=178]");return EVENT_BLOCK;}
		if (NULL != (strstr((char*)msg.c_str(), "p社") || strstr((char*)msg.c_str(), "P社") || strstr((char*)msg.c_str(), "鬼畜音mad") || strstr((char*)msg.c_str(), "光复汉室")))
		{CQ_setGroupBan(ac, fromGroup, fromQQ, 60);CQ_sendGroupMsg(ac, fromGroup, "[CQ:face,id=178]");return EVENT_BLOCK;}
		if (NULL != (strstr((char*)msg.c_str(), "天神下凡1v4") || strstr((char*)msg.c_str(), "天神下凡1V4")|| strstr((char*)msg.c_str(), "匡扶汉室")))
		{CQ_setGroupBan(ac, fromGroup, fromQQ, 60);CQ_sendGroupMsg(ac, fromGroup, "[CQ:face,id=178]");return EVENT_BLOCK;}
		if (NULL != (strstr((char*)msg.c_str(), "六四")))
		{CQ_setGroupBan(ac, fromGroup, fromQQ, 60);CQ_sendGroupMsg(ac, fromGroup, "[CQ:face,id=178]");return EVENT_BLOCK;}
		if (NULL != (strstr((char*)msg.c_str(), "杰哥不要") || strstr((char*)msg.c_str(), "带带大师兄")))
		{CQ_setGroupBan(ac, fromGroup, fromQQ, 60);CQ_sendGroupMsg(ac, fromGroup, "[CQ:face,id=178]");return EVENT_BLOCK;}
	}

	//问好
	if (NULL != strstr((char*)msg.c_str(), "大酱早安"))
		{CQ_sendGroupMsg(ac, fromGroup, "おはよ");return EVENT_BLOCK;}
	else if (NULL != strstr((char*)msg.c_str(), "大酱晚安"))
		{CQ_sendGroupMsg(ac, fromGroup, "おやすみ");return EVENT_BLOCK;}
	else if (NULL != (strstr((char*)msg.c_str(), "大酱中午好")|| strstr((char*)msg.c_str(), "大酱午安")))
		{CQ_sendGroupMsg(ac, fromGroup, "中午好鸭");return EVENT_BLOCK;}
	else if (NULL != strstr((char*)msg.c_str(), "大酱"))
		{CQ_sendGroupMsg(ac, fromGroup, "はい");}
	else if (NULL != (strstr((char*)msg.c_str(), "社会") || strstr((char*)msg.c_str(), "可怕")))
	{CQ_sendGroupMsg(ac, fromGroup, "社会社会[CQ:face,id=178]");return EVENT_BLOCK;}
	else if (NULL != (strstr((char*)msg.c_str(), "AMD")|| strstr((char*)msg.c_str(), "amd")))
		{CQ_sendGroupMsg(ac, fromGroup, "Intel牛逼！[CQ:face,id=178]");return EVENT_BLOCK;}
	else if (NULL != strstr((char*)msg.c_str(), "鲍"))
		{CQ_sendGroupMsg(ac, fromGroup, "不许骂我家⑨，混蛋[CQ:face,id=31]");
		srand((unsigned)time(NULL));
		if (rand() % 2 && fromGroup == 719120383)
			{CQ_setGroupBan(ac, fromGroup, fromQQ, 60);CQ_sendGroupMsg(ac, fromGroup, "[CQ:face,id=178]");}
		return EVENT_BLOCK;}
	else {}

	//复读
	if ("复读" == msg.substr(0, 4))
	{msg = msg.substr(4);msg.insert(0, "] \n");msg.insert(0, std::to_string(fromQQ));msg.insert(0, "[CQ:at,qq=");CQ_sendGroupMsg(ac, fromGroup, (char*)msg.c_str());return EVENT_BLOCK;}

	//随机选择
	if ("/随机选择" == msg.substr(0, 9))
	{
		msg.erase(0, 10);				//gb10830编码一个字符占两个字节
		int i = 0, flag = 0;			//i记录‘|’个数，flag记录‘|’下标
		for (i = -1;flag >= 0;i++)
		{
			flag = msg.find('|', flag + 1);
		}
		srand((unsigned)time(NULL));
		int choose = rand() % (i + 1);	//choose记录大酱的选择（从0开始）
		i = 0, flag = 0;				//i和flag重新初始化
		for (i = 0,flag = 0;i < choose;i++)
		{
			flag = msg.find('|', flag + 1);
		}
		msg = msg.substr(flag);
		if ('|' == msg[0])				//除去可能的前置'|'
		{
			msg = msg.substr(1);
		}
		flag = msg.find('|');			//除去可能的后置'|'
		if (-1 != flag)
		{
			msg = msg.substr(0, flag);
		}
		msg = "嗯，大酱选择了" + msg;
		msg += "的说(≧▽≦)";
		CQ_sendGroupMsg(ac, fromGroup, (char*)msg.c_str());
		return EVENT_BLOCK;
	}

	//随机复读
	srand((unsigned)time(NULL));
	if (!(rand() % 100))
	{CQ_sendGroupMsg(ac, fromGroup, (char*)msg.c_str());return EVENT_BLOCK;}


	return EVENT_IGNORE; //关于返回值说明, 见“_eventPrivateMsg”函数
}


/*
* Type=4 讨论组消息
*/
CQEVENT(int32_t, __eventDiscussMsg, 32)(int32_t subType, int32_t msgId, int64_t fromDiscuss, int64_t fromQQ, const char *themsg, int32_t font) {
	string msg = themsg;

	//版本信息
	if (msg == "-help")
	{CQ_sendDiscussMsg(ac, fromDiscuss, "自己摸索的说");return EVENT_BLOCK;}
	if (msg == "-about")
	{CQ_sendDiscussMsg(ac, fromDiscuss, "version:0.0.2\nversion_id:2\nauthor:Bao Peize");return EVENT_BLOCK;}

	//问好
	if (NULL != strstr((char*)msg.c_str(), "大酱早安"))
	{CQ_sendDiscussMsg(ac, fromDiscuss, "おはよ");return EVENT_BLOCK;}
	else if (NULL != strstr((char*)msg.c_str(), "大酱晚安"))
	{CQ_sendDiscussMsg(ac, fromDiscuss, "おやすみ");return EVENT_BLOCK;}
	else if (NULL != (strstr((char*)msg.c_str(), "大酱中午好") || strstr((char*)msg.c_str(), "大酱午安")))
	{CQ_sendDiscussMsg(ac, fromDiscuss, "中午好鸭");return EVENT_BLOCK;}
	else if (NULL != strstr((char*)msg.c_str(), "大酱"))
	{CQ_sendDiscussMsg(ac, fromDiscuss, "はい");}
	else if (NULL != (strstr((char*)msg.c_str(), "社会") || strstr((char*)msg.c_str(), "可怕")))
	{CQ_sendDiscussMsg(ac, fromDiscuss, "社会社会[CQ:face,id=178]");return EVENT_BLOCK;}
	else if (NULL != (strstr((char*)msg.c_str(), "AMD") || strstr((char*)msg.c_str(), "amd")))
	{CQ_sendDiscussMsg(ac, fromDiscuss, "Intel牛逼！[CQ:face,id=178]");return EVENT_BLOCK;}
	else {}

	//复读
	if ("复读" == msg.substr(0, 4))
	{msg = msg.substr(4);msg.insert(0, "] \n");msg.insert(0, std::to_string(fromQQ));msg.insert(0, "[CQ:at,qq=");CQ_sendDiscussMsg(ac, fromDiscuss, (char*)msg.c_str());return EVENT_BLOCK;}

	//随机选择
	if ("/随机选择" == msg.substr(0, 9))
	{
		msg.erase(0, 10);				//gb10830编码一个字符占两个字节
		int i = 0, flag = 0;			//i记录‘|’个数，flag记录‘|’下标
		for (i = -1;flag >= 0;i++)
		{
			flag = msg.find('|', flag + 1);
		}
		srand((unsigned)time(NULL));
		int choose = rand() % (i + 1);	//choose记录大酱的选择（从0开始）
		i = 0, flag = 0;				//i和flag重新初始化
		for (i = 0, flag = 0;i < choose;i++)
		{
			flag = msg.find('|', flag + 1);
		}
		msg = msg.substr(flag);
		if ('|' == msg[0])				//除去可能的前置'|'
		{
			msg = msg.substr(1);
		}
		flag = msg.find('|');			//除去可能的后置'|'
		if (-1 != flag)
		{
			msg = msg.substr(0, flag);
		}
		msg = "嗯，大酱选择了" + msg;
		msg += "的说(≧▽≦)";
		CQ_sendDiscussMsg(ac, fromDiscuss, (char*)msg.c_str());
		return EVENT_BLOCK;
	}

	//随机复读
	srand((unsigned)time(NULL));
	if (!(rand() % 100))
	{CQ_sendDiscussMsg(ac, fromDiscuss, (char*)msg.c_str());return EVENT_BLOCK;}


	return EVENT_IGNORE; //关于返回值说明, 见“_eventPrivateMsg”函数
}


/*
* Type=101 群事件-管理员变动
* subType 子类型，1/被取消管理员 2/被设置管理员
*/
CQEVENT(int32_t, __eventSystem_GroupAdmin, 24)(int32_t subType, int32_t sendTime, int64_t fromGroup, int64_t beingOperateQQ) {

	return EVENT_IGNORE; //关于返回值说明, 见“_eventPrivateMsg”函数
}


/*
* Type=102 群事件-群成员减少
* subType 子类型，1/群员离开 2/群员被踢 3/自己(即登录号)被踢
* fromQQ 操作者QQ(仅subType为2、3时存在)
* beingOperateQQ 被操作QQ
*/
CQEVENT(int32_t, __eventSystem_GroupMemberDecrease, 32)(int32_t subType, int32_t sendTime, int64_t fromGroup, int64_t fromQQ, int64_t beingOperateQQ) {

	return EVENT_IGNORE; //关于返回值说明, 见“_eventPrivateMsg”函数
}


/*
* Type=103 群事件-群成员增加
* subType 子类型，1/管理员已同意 2/管理员邀请
* fromQQ 操作者QQ(即管理员QQ)
* beingOperateQQ 被操作QQ(即加群的QQ)
*/
CQEVENT(int32_t, __eventSystem_GroupMemberIncrease, 32)(int32_t subType, int32_t sendTime, int64_t fromGroup, int64_t fromQQ, int64_t beingOperateQQ) {

	return EVENT_IGNORE; //关于返回值说明, 见“_eventPrivateMsg”函数
}


/*
* Type=201 好友事件-好友已添加
*/
CQEVENT(int32_t, __eventFriend_Add, 16)(int32_t subType, int32_t sendTime, int64_t fromQQ) {

	return EVENT_IGNORE; //关于返回值说明, 见“_eventPrivateMsg”函数
}


/*
* Type=301 请求-好友添加
* msg 附言
* responseFlag 反馈标识(处理请求用)
*/
CQEVENT(int32_t, __eventRequest_AddFriend, 24)(int32_t subType, int32_t sendTime, int64_t fromQQ, const char *msg, const char *responseFlag) {

	//CQ_setFriendAddRequest(ac, responseFlag, REQUEST_ALLOW, "");

	return EVENT_IGNORE; //关于返回值说明, 见“_eventPrivateMsg”函数
}


/*
* Type=302 请求-群添加
* subType 子类型，1/他人申请入群 2/自己(即登录号)受邀入群
* msg 附言
* responseFlag 反馈标识(处理请求用)
*/
CQEVENT(int32_t, __eventRequest_AddGroup, 32)(int32_t subType, int32_t sendTime, int64_t fromGroup, int64_t fromQQ, const char *msg, const char *responseFlag) {

	//if (subType == 1) {
	//	CQ_setGroupAddRequestV2(ac, responseFlag, REQUEST_GROUPADD, REQUEST_ALLOW, "");
	//} else if (subType == 2) {
	//	CQ_setGroupAddRequestV2(ac, responseFlag, REQUEST_GROUPINVITE, REQUEST_ALLOW, "");
	//}

	return EVENT_IGNORE; //关于返回值说明, 见“_eventPrivateMsg”函数
}

/*
* 菜单，可在 .json 文件中设置菜单数目、函数名
* 如果不使用菜单，请在 .json 及此处删除无用菜单
*/
CQEVENT(int32_t, __menuA, 0)() {
	MessageBoxA(NULL, "这是menuA，在这里载入窗口，或者进行其他工作。", "" ,0);
	return 0;
}

CQEVENT(int32_t, __menuB, 0)() {
	MessageBoxA(NULL, "这是menuB，在这里载入窗口，或者进行其他工作。", "" ,0);
	return 0;
}
