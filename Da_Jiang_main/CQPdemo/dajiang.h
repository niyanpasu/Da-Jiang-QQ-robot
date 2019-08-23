#pragma once

//µÈ´ıÍêÉÆ

#include<iostream>
//²éÕÒ
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