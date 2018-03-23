#ifndef GLOBAL_H
#define GLOBAL_H
using namespace std;

typedef struct _DATAITEM
{
	string project_id;
	string project_name;
	long msec; //毫秒数   
	int resLength;
	string recvModule;
	string sendbuf;
	string recvbuf;
	int error_code;
	string serverIP;
	string sDomainName;
}DATAITEM;

//去前后空白字符
void trim(string &str);
bool isSpace(char c);
void trimLeft(string &str);
void trimRight(string &str);

//获取IP地址
unsigned int getAddr ( const char *szHost);

//把时间格式化成字符串
void FormatTime2Str(time_t time1, char* szTime);

//把时间字符串转化成时间
time_t FormatStr2Time(char* szTime);

#endif
