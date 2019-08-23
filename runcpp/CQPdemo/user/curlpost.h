#pragma once
#define CURL_STATICLIB
#include "../libcurl/curl/curl.h"
#include <string>
std::string UTF8ToGBK(const std::string& strUTF8);
std::string GBKToUTF8(const std::string& strGBK);
std::string escape(const std::string & POSTFIELDS);
std::string curlpost(const char * POSTURL, const char * POSTFIELDS);
