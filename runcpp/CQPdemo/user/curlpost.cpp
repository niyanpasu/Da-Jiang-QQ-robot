#include"curlpost.h"
using namespace std;
string UTF8ToGBK(const std::string & strUTF8)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, strUTF8.c_str(), -1, NULL, 0);
	WCHAR* wszGBK = new WCHAR[len + 1];
	memset(wszGBK, 0, len * 2 + 2);
	MultiByteToWideChar(CP_UTF8, 0, (LPCCH)strUTF8.c_str(), -1, wszGBK, len);
	len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);
	char *szGBK = new char[len + 1];
	memset(szGBK, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, szGBK, len, NULL, NULL);
	std::string strTemp(szGBK);
	delete[]szGBK;
	delete[]wszGBK;
	return strTemp;
}
string GBKToUTF8(const std::string & strGBK)
{
	string strOutUTF8 = "";
	WCHAR * str1;
	int n = MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, NULL, 0);
	str1 = new WCHAR[n];
	MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, str1, n);
	n = WideCharToMultiByte(CP_UTF8, 0, str1, -1, NULL, 0, NULL, NULL);
	char * str2 = new char[n];
	WideCharToMultiByte(CP_UTF8, 0, str1, -1, str2, n, NULL, NULL);
	strOutUTF8 = str2;
	delete[]str1;
	delete[]str2;
	return strOutUTF8;
}
size_t write_data(void * buffer, size_t size, size_t nmemb, void * userp)
{
	(*static_cast<std::string *>(userp)) += string{ (char *)buffer };
	return nmemb;
}
string escape(const std::string & POSTFIELDS) {
	CURL* curl = curl_easy_init(); 
	string outputstr;
	char *output1 = curl_easy_escape(curl, POSTFIELDS.c_str(), POSTFIELDS.size());
	outputstr = output1;
	curl_free(output1);
	curl_easy_cleanup(curl);
	return outputstr;

}
string curlpost(const char * POSTURL, const char * POSTFIELDS) {
	curl_global_init(CURL_GLOBAL_ALL); 
	CURL * curl = curl_easy_init(); 
	if (NULL == curl) { return 0; }
	string my_param = "";
	curl_easy_setopt(curl, CURLOPT_URL, POSTURL);
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, POSTFIELDS);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &my_param);
	CURLcode res = curl_easy_perform(curl);
	curl_easy_cleanup(curl);
	return my_param;
}
