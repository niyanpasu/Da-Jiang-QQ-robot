#pragma once
#include<iostream>
#include<cstring>
#include<time.h>
#include<fstream>//文件操作
#include <regex>//正则操作
using namespace std;

//API调用
#include <tchar.h>
#include <windows.h>
#include<urlmon.h>
#pragma comment(lib, "urlmon.lib")

//版本信息
string about(string str_in) {
	if (str_in == "-help"){
		return "自己摸索的说";
	}
	if (str_in == "-about"){
		return "version:0.0.3\nversion_id:3\nauthor:Bao Peize";
	}
	return "Dajiang_not_found";
}

//问好
string hello(string str_in) {
	if (NULL != strstr((char*)str_in.c_str(), "大酱早安")){
		return "おはよ";
	}
	if (NULL != strstr((char*)str_in.c_str(), "大酱晚安")){
		return  "おやすみ";
	}
	if (NULL != (strstr((char*)str_in.c_str(), "大酱中午好") || strstr((char*)str_in.c_str(), "大酱午安"))){
		return "中午好鸭";
	}
	if (NULL != (strstr((char*)str_in.c_str(), "社会") || strstr((char*)str_in.c_str(), "可怕"))){
		return "社会社会[CQ:face,id=178]";
	}
	if (NULL != (strstr((char*)str_in.c_str(), "AMD") || strstr((char*)str_in.c_str(), "amd"))){
		return "Intel牛逼！[CQ:face,id=178]";
	}
	return "Dajiang_not_found";
}

//复读
string repeat_Private(string str_in, int64_t fromQQ) {
	if ("复读" == str_in.substr(0, 4)){
		str_in = str_in.substr(4);
		return str_in;
	}
	return "Dajiang_not_found";
}
string repeat(string str_in, int64_t fromQQ) {
	if ("复读" == str_in.substr(0, 4)) {
		str_in = str_in.substr(4);
		/*str_in.insert(0, "] \n");
		str_in.insert(0, std::to_string(fromQQ));
		str_in.insert(0, "[CQ:at,qq=");*/
		return str_in;
	}
	return "Dajiang_not_found";
}

//随机选择
string random_choice(string str_in) {
	if ("/随机选择" == str_in.substr(0, 9))
	{
		str_in.erase(0, 10);				//gb10830编码一个字符占两个字节
		int i = 0, flag = 0;			//i记录‘|’个数，flag记录‘|’下标
		for (i = -1;flag >= 0;i++)
		{
			flag = str_in.find('|', flag + 1);
		}
		srand((unsigned)time(NULL));
		int choose = rand() % (i + 1);	//choose记录大酱的选择（从0开始）
		i = 0, flag = 0;				//i和flag重新初始化
		for (i = 0, flag = 0;i < choose;i++)
		{
			flag = str_in.find('|', flag + 1);
		}
		str_in = str_in.substr(flag);
		if ('|' == str_in[0])				//除去可能的前置'|'
		{
			str_in = str_in.substr(1);
		}
		flag = str_in.find('|');			//除去可能的后置'|'
		if (-1 != flag)
		{
			str_in = str_in.substr(0, flag);
		}
		str_in = "嗯，大酱选择了" + str_in;
		str_in += "的说(≧▽≦)";
		return str_in;
	}
	return "Dajiang_not_found";
}

//禁言(迫害狗群员)
int ban(string str_in,int64_t fromGroup, int64_t fromQQ) {
	if (fromGroup == 719120383){
		if (NULL != (strstr((char*)str_in.c_str(), "cxk") || (strstr((char*)str_in.c_str(), "菜") && strstr((char*)str_in.c_str(), "虚") && strstr((char*)str_in.c_str(), "鲲")))){
			return 60;
		}
		if (NULL != (strstr((char*)str_in.c_str(), "esu") || strstr((char*)str_in.c_str(), "pronhub") || strstr((char*)str_in.c_str(), "SSR") || strstr((char*)str_in.c_str(), "V2Ray"))){
			return 60;
		}
		if (NULL != (strstr((char*)str_in.c_str(), "平胸怪") || strstr((char*)str_in.c_str(), "野兽先辈") || strstr((char*)str_in.c_str(), "昏睡红茶") || strstr((char*)str_in.c_str(), "雷普"))){
			return 60;
		}
		if (NULL != (strstr((char*)str_in.c_str(), "比利") || strstr((char*)str_in.c_str(), "哲学") || strstr((char*)str_in.c_str(), "出柜"))){
			return 60;
		}
		if (NULL != (strstr((char*)str_in.c_str(), "p社") || strstr((char*)str_in.c_str(), "P社") || strstr((char*)str_in.c_str(), "鬼畜音mad") || strstr((char*)str_in.c_str(), "光复汉室"))){
			return 60;
		}
		if (NULL != (strstr((char*)str_in.c_str(), "天神下凡1v4") || strstr((char*)str_in.c_str(), "天神下凡1V4") || strstr((char*)str_in.c_str(), "匡扶汉室"))){
			return 60;
		}
		if (NULL != (strstr((char*)str_in.c_str(), "六四"))){
			return 60;
		}
		if (NULL != (strstr((char*)str_in.c_str(), "杰哥不要") || strstr((char*)str_in.c_str(), "带带大师兄"))){
			return 60;
		}
		return 0;
	}
	return 0;
}

//色图
int setu_get(string str_in) {
	if (std::regex_search(str_in, std::regex("(大酱.*[来來发發给給张章个份].*[色瑟]+[图圖])|(大酱.*[来來发發给給张章个份].*setu)"))){
		TCHAR url[] = TEXT("https://img.paulzzh.tech/touhou/random?site=all&size=all");
		TCHAR filePath[] = _T("E:\\酷Q Pro\\data\\image\\setu.jpg");
		HRESULT res = URLDownloadToFile(NULL, url, filePath, 0, NULL);
		if (res == S_OK) {
			return 1;//OK,成功
		}
		else if (res == E_OUTOFMEMORY) {
			return 2;//Buffer length invalid, or insufficient memory
		}
		else if (res == INET_E_DOWNLOAD_FAILURE) {
			return 3;//URL is invalid
		}
		else {
			return 4;//printf("Other error: %d\n", res);
		}
		//记得在调用后删除文件
	}
	return 0;
}
/*
int flag_test = 1;
int judge() {
	
	return flag_test++;
}

if (std::regex_match(str_in, std::regex("(大酱.*[来來发發给給].*[色瑟][图圖])|(--setu)"))){
		int i = judge();
		msg = to_string(i);
		CQ_sendPrivateMsg(ac, fromQQ, (char*)msg.c_str());return EVENT_BLOCK;
}
	
*/

/*
//查找
using namespace std;
class find {
	public:
		find(string c_msg):msg(c_msg){}
		~find() {}
		string finding(string c_msg)
		{
			msg = c_msg;
			for (int i = 0;i < 100;i++)
			{
				if (msg.find(i_msg[i]))
					return o_msg[i];
			}
			return NULL;
		}
	private:
		string msg;
		static string i_msg[100],o_msg[100];
};
*/