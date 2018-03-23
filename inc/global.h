#ifndef GLOBAL_H
#define GLOBAL_H
using namespace std;

typedef struct _DATAITEM
{
	string project_id;
	string project_name;
	long msec; //������   
	int resLength;
	string recvModule;
	string sendbuf;
	string recvbuf;
	int error_code;
	string serverIP;
	string sDomainName;
}DATAITEM;

//ȥǰ��հ��ַ�
void trim(string &str);
bool isSpace(char c);
void trimLeft(string &str);
void trimRight(string &str);

//��ȡIP��ַ
unsigned int getAddr ( const char *szHost);

//��ʱ���ʽ�����ַ���
void FormatTime2Str(time_t time1, char* szTime);

//��ʱ���ַ���ת����ʱ��
time_t FormatStr2Time(char* szTime);

#endif
