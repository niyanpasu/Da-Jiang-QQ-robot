#pragma once
#include<iostream>
#include<cstring>
#include<time.h>
#include<fstream>//猟周荷恬
#include <regex>//屎夸荷恬
using namespace std;

//API距喘
#include <tchar.h>
#include <windows.h>
#include<urlmon.h>
#pragma comment(lib, "urlmon.lib")

//井云佚連
string about(string str_in) {
	if (str_in == "-help"){
		return "徭失寵沫議傍";
	}
	if (str_in == "-about"){
		return "version:0.0.3\nversion_id:3\nauthor:Bao Peize";
	}
	return "Dajiang_not_found";
}

//諒挫
string hello(string str_in) {
	if (NULL != strstr((char*)str_in.c_str(), "寄輯壼芦")){
		return "おはよ";
	}
	if (NULL != strstr((char*)str_in.c_str(), "寄輯絡芦")){
		return  "おやすみ";
	}
	if (NULL != (strstr((char*)str_in.c_str(), "寄輯嶄怜挫") || strstr((char*)str_in.c_str(), "寄輯怜芦"))){
		return "嶄怜挫兌";
	}
	if (NULL != (strstr((char*)str_in.c_str(), "芙氏") || strstr((char*)str_in.c_str(), "辛殿"))){
		return "芙氏芙氏[CQ:face,id=178]";
	}
	if (NULL != (strstr((char*)str_in.c_str(), "AMD") || strstr((char*)str_in.c_str(), "amd"))){
		return "Intel釘影��[CQ:face,id=178]";
	}
	return "Dajiang_not_found";
}

//鹸響
string repeat_Private(string str_in, int64_t fromQQ) {
	if ("鹸響" == str_in.substr(0, 4)){
		str_in = str_in.substr(4);
		return str_in;
	}
	return "Dajiang_not_found";
}
string repeat(string str_in, int64_t fromQQ) {
	if ("鹸響" == str_in.substr(0, 4)) {
		str_in = str_in.substr(4);
		/*str_in.insert(0, "] \n");
		str_in.insert(0, std::to_string(fromQQ));
		str_in.insert(0, "[CQ:at,qq=");*/
		return str_in;
	}
	return "Dajiang_not_found";
}

//昧字僉夲
string random_choice(string str_in) {
	if ("/昧字僉夲" == str_in.substr(0, 9))
	{
		str_in.erase(0, 10);				//gb10830園鷹匯倖忖憲媼曾倖忖准
		int i = 0, flag = 0;			//i芝村｀|¨倖方��flag芝村｀|¨和炎
		for (i = -1;flag >= 0;i++)
		{
			flag = str_in.find('|', flag + 1);
		}
		srand((unsigned)time(NULL));
		int choose = rand() % (i + 1);	//choose芝村寄輯議僉夲�┫�0蝕兵��
		i = 0, flag = 0;				//i才flag嶷仟兜兵晒
		for (i = 0, flag = 0;i < choose;i++)
		{
			flag = str_in.find('|', flag + 1);
		}
		str_in = str_in.substr(flag);
		if ('|' == str_in[0])				//茅肇辛嬬議念崔'|'
		{
			str_in = str_in.substr(1);
		}
		flag = str_in.find('|');			//茅肇辛嬬議朔崔'|'
		if (-1 != flag)
		{
			str_in = str_in.substr(0, flag);
		}
		str_in = "狹��寄輯僉夲阻" + str_in;
		str_in += "議傍(�R���Q)";
		return str_in;
	}
	return "Dajiang_not_found";
}

//鋤冱(独墾昂蛤埀)
int ban(string str_in,int64_t fromGroup, int64_t fromQQ) {
	if (fromGroup == 719120383){
		if (NULL != (strstr((char*)str_in.c_str(), "cxk") || (strstr((char*)str_in.c_str(), "暇") && strstr((char*)str_in.c_str(), "倡") && strstr((char*)str_in.c_str(), "��")))){
			return 60;
		}
		if (NULL != (strstr((char*)str_in.c_str(), "esu") || strstr((char*)str_in.c_str(), "pronhub") || strstr((char*)str_in.c_str(), "SSR") || strstr((char*)str_in.c_str(), "V2Ray"))){
			return 60;
		}
		if (NULL != (strstr((char*)str_in.c_str(), "峠俟講") || strstr((char*)str_in.c_str(), "勸舗枠渦") || strstr((char*)str_in.c_str(), "肢鋒碕画") || strstr((char*)str_in.c_str(), "跡噸"))){
			return 60;
		}
		if (NULL != (strstr((char*)str_in.c_str(), "曳旋") || strstr((char*)str_in.c_str(), "學僥") || strstr((char*)str_in.c_str(), "竃国"))){
			return 60;
		}
		if (NULL != (strstr((char*)str_in.c_str(), "p芙") || strstr((char*)str_in.c_str(), "P芙") || strstr((char*)str_in.c_str(), "麹偕咄mad") || strstr((char*)str_in.c_str(), "高鹸査片"))){
			return 60;
		}
		if (NULL != (strstr((char*)str_in.c_str(), "爺舞和群1v4") || strstr((char*)str_in.c_str(), "爺舞和群1V4") || strstr((char*)str_in.c_str(), "随喧査片"))){
			return 60;
		}
		if (NULL != (strstr((char*)str_in.c_str(), "鎗膨"))){
			return 60;
		}
		if (NULL != (strstr((char*)str_in.c_str(), "旬悟音勣") || strstr((char*)str_in.c_str(), "揮揮寄弗儘"))){
			return 60;
		}
		return 0;
	}
	return 0;
}

//弼夕
int setu_get(string str_in) {
	if (std::regex_search(str_in, std::regex("(寄輯.*[栖�躔��l公�o嫖嫗倖芸].*[弼肘]+[夕�D])|(寄輯.*[栖�躔��l公�o嫖嫗倖芸].*setu)"))){
		TCHAR url[] = TEXT("https://img.paulzzh.tech/touhou/random?site=all&size=all");
		TCHAR filePath[] = _T("E:\\吹Q Pro\\data\\image\\setu.jpg");
		HRESULT res = URLDownloadToFile(NULL, url, filePath, 0, NULL);
		if (res == S_OK) {
			return 1;//OK,撹孔
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
		//芝誼壓距喘朔評茅猟周
	}
	return 0;
}
/*
int flag_test = 1;
int judge() {
	
	return flag_test++;
}

if (std::regex_match(str_in, std::regex("(寄輯.*[栖�躔��l公�o].*[弼肘][夕�D])|(--setu)"))){
		int i = judge();
		msg = to_string(i);
		CQ_sendPrivateMsg(ac, fromQQ, (char*)msg.c_str());return EVENT_BLOCK;
}
	
*/

/*
//臥孀
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