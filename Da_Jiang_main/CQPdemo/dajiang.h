#pragma once
#include<iostream>
#include<cstring>
#include<time.h>
#include<fstream>//�ļ�����
#include <regex>//�������
using namespace std;

//API����
#include <tchar.h>
#include <windows.h>
#include<urlmon.h>
#pragma comment(lib, "urlmon.lib")

//�汾��Ϣ
string about(string str_in) {
	if (str_in == "-help"){
		return "�Լ�������˵";
	}
	if (str_in == "-about"){
		return "version:0.0.3\nversion_id:3\nauthor:Bao Peize";
	}
	return "Dajiang_not_found";
}

//�ʺ�
string hello(string str_in) {
	if (NULL != strstr((char*)str_in.c_str(), "���簲")){
		return "���Ϥ�";
	}
	if (NULL != strstr((char*)str_in.c_str(), "����")){
		return  "���䤹��";
	}
	if (NULL != (strstr((char*)str_in.c_str(), "�������") || strstr((char*)str_in.c_str(), "���簲"))){
		return "�����Ѽ";
	}
	if (NULL != (strstr((char*)str_in.c_str(), "���") || strstr((char*)str_in.c_str(), "����"))){
		return "������[CQ:face,id=178]";
	}
	if (NULL != (strstr((char*)str_in.c_str(), "AMD") || strstr((char*)str_in.c_str(), "amd"))){
		return "Intelţ�ƣ�[CQ:face,id=178]";
	}
	return "Dajiang_not_found";
}

//����
string repeat_Private(string str_in, int64_t fromQQ) {
	if ("����" == str_in.substr(0, 4)){
		str_in = str_in.substr(4);
		return str_in;
	}
	return "Dajiang_not_found";
}
string repeat(string str_in, int64_t fromQQ) {
	if ("����" == str_in.substr(0, 4)) {
		str_in = str_in.substr(4);
		/*str_in.insert(0, "] \n");
		str_in.insert(0, std::to_string(fromQQ));
		str_in.insert(0, "[CQ:at,qq=");*/
		return str_in;
	}
	return "Dajiang_not_found";
}

//���ѡ��
string random_choice(string str_in) {
	if ("/���ѡ��" == str_in.substr(0, 9))
	{
		str_in.erase(0, 10);				//gb10830����һ���ַ�ռ�����ֽ�
		int i = 0, flag = 0;			//i��¼��|��������flag��¼��|���±�
		for (i = -1;flag >= 0;i++)
		{
			flag = str_in.find('|', flag + 1);
		}
		srand((unsigned)time(NULL));
		int choose = rand() % (i + 1);	//choose��¼�󽴵�ѡ�񣨴�0��ʼ��
		i = 0, flag = 0;				//i��flag���³�ʼ��
		for (i = 0, flag = 0;i < choose;i++)
		{
			flag = str_in.find('|', flag + 1);
		}
		str_in = str_in.substr(flag);
		if ('|' == str_in[0])				//��ȥ���ܵ�ǰ��'|'
		{
			str_in = str_in.substr(1);
		}
		flag = str_in.find('|');			//��ȥ���ܵĺ���'|'
		if (-1 != flag)
		{
			str_in = str_in.substr(0, flag);
		}
		str_in = "�ţ���ѡ����" + str_in;
		str_in += "��˵(�R���Q)";
		return str_in;
	}
	return "Dajiang_not_found";
}

//����(�Ⱥ���ȺԱ)
int ban(string str_in,int64_t fromGroup, int64_t fromQQ) {
	if (fromGroup == 719120383){
		if (NULL != (strstr((char*)str_in.c_str(), "cxk") || (strstr((char*)str_in.c_str(), "��") && strstr((char*)str_in.c_str(), "��") && strstr((char*)str_in.c_str(), "��")))){
			return 60;
		}
		if (NULL != (strstr((char*)str_in.c_str(), "esu") || strstr((char*)str_in.c_str(), "pronhub") || strstr((char*)str_in.c_str(), "SSR") || strstr((char*)str_in.c_str(), "V2Ray"))){
			return 60;
		}
		if (NULL != (strstr((char*)str_in.c_str(), "ƽ�ع�") || strstr((char*)str_in.c_str(), "Ұ���ȱ�") || strstr((char*)str_in.c_str(), "��˯���") || strstr((char*)str_in.c_str(), "����"))){
			return 60;
		}
		if (NULL != (strstr((char*)str_in.c_str(), "����") || strstr((char*)str_in.c_str(), "��ѧ") || strstr((char*)str_in.c_str(), "����"))){
			return 60;
		}
		if (NULL != (strstr((char*)str_in.c_str(), "p��") || strstr((char*)str_in.c_str(), "P��") || strstr((char*)str_in.c_str(), "������mad") || strstr((char*)str_in.c_str(), "�⸴����"))){
			return 60;
		}
		if (NULL != (strstr((char*)str_in.c_str(), "�����·�1v4") || strstr((char*)str_in.c_str(), "�����·�1V4") || strstr((char*)str_in.c_str(), "�������"))){
			return 60;
		}
		if (NULL != (strstr((char*)str_in.c_str(), "����"))){
			return 60;
		}
		if (NULL != (strstr((char*)str_in.c_str(), "�ܸ粻Ҫ") || strstr((char*)str_in.c_str(), "������ʦ��"))){
			return 60;
		}
		return 0;
	}
	return 0;
}

//ɫͼ
int setu_get(string str_in) {
	if (std::regex_search(str_in, std::regex("(��.*[�����l���o���¸���].*[ɫɪ]+[ͼ�D])|(��.*[�����l���o���¸���].*setu)"))){
		TCHAR url[] = TEXT("https://img.paulzzh.tech/touhou/random?site=all&size=all");
		TCHAR filePath[] = _T("E:\\��Q Pro\\data\\image\\setu.jpg");
		HRESULT res = URLDownloadToFile(NULL, url, filePath, 0, NULL);
		if (res == S_OK) {
			return 1;//OK,�ɹ�
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
		//�ǵ��ڵ��ú�ɾ���ļ�
	}
	return 0;
}
/*
int flag_test = 1;
int judge() {
	
	return flag_test++;
}

if (std::regex_match(str_in, std::regex("(��.*[�����l���o].*[ɫɪ][ͼ�D])|(--setu)"))){
		int i = judge();
		msg = to_string(i);
		CQ_sendPrivateMsg(ac, fromQQ, (char*)msg.c_str());return EVENT_BLOCK;
}
	
*/

/*
//����
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