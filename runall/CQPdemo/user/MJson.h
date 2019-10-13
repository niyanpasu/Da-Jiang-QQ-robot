#pragma once
#include <string>
#include <memory>
#include "../jsoncpp/json/json.h"
/* �ı�JsonCpp��ĳЩ��Ϊ,���ڴ���ֻ����Json */
class MJson:public Json::Value
{
public:
	//����Json�ַ���
	MJson(Json::Value v)
	{
		this->swap(v);
	}
	MJson(const std::string & str) 
	{
		std::unique_ptr<Json::CharReader> const jsonReader(Json::CharReaderBuilder().newCharReader());
		jsonReader->parse(str.c_str(), str.c_str() + str.length(), this, &errs);
	}
	/* ����key�� json �ַ�����ȡvalue*/
	MJson operator[](const std::string & key) {
		int i = 3;
		if (!(isMember(key))) {
			throw std::exception(("The key '" + key + "' is not exists").c_str());
		}
		return Json::Value::operator[](key);
	}
private:
	JSONCPP_STRING errs;
};

