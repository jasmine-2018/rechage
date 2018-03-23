#ifdef WIN32
#include "stdafx.h"
#include "winsock2.h"
#else
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h> 
#endif
#include <stdio.h>
#include <iostream>
#include <string.h>
#include "global.h"

bool isSpace(char c);
void trimLeft(string &str);
void trimRight(string &str);
void hex2string(const unsigned char* hex, int hexLen, char* str, int *len);

bool isSpace(char c) 
{ 
	switch (c) 
	{ 
		default: 
				return false; 
		case ' ': 
		case '\r': 
		case '\n': 
		case '\t': 
		case '\v': 
				return true; 
	} 
} 

void trimLeft(string & str) 
{ 
	string::iterator iBegin, strBegin, strEnd; 
	for(iBegin=strBegin=str.begin(), strEnd=str.end(); iBegin!=strEnd; iBegin++) 
	{ 
		if (!isSpace(*iBegin)) 
		{ 
			break; 
		} 
	} 

	if (iBegin!=strBegin) 
	{ 
		unsigned int nSize= 0; 
		for(; iBegin!=strEnd; strBegin++, iBegin++, nSize++) 
		{ 
			(*strBegin)= (*iBegin); 
		} 

		str.resize(nSize); 
	} 
} 

void trimRight(string & str) 
{ 
	string::reverse_iterator i, strBegin; 
	unsigned int nSize= str.length(); 

	for(i=str.rbegin(), strBegin=str.rend(); i!=strBegin; i++) 
	{ 
		if (isSpace(char(*i))) 
		{ 
			nSize--; 
		} 
		else 
		{ 
			break; 
		} 
	} 

	str.resize(nSize); 
}
void trim(string & str)
{
	trimLeft(str);
	trimRight(str);
}

void hex2string(const unsigned char* hex, int hexLen, char* str, int *len)
{
	int i, o;
	for (i=0, o=0; i<hexLen; i++, o+=2)
	{
		sprintf(&str[o], "%02X", hex[i]);
	}
}

char ConvertHexChar(char ch) 
{
	if((ch>='0')&&(ch<='9'))
		return ch-0x30;
	else if((ch>='A')&&(ch<='F'))
		return ch-'A'+10;
	else if((ch>='a')&&(ch<='f'))
		return ch-'a'+10;
	else 
		return (-1);
}

/*-----------------------------------------------------------
 * Function: getAddr()
 *
 * Description: Given a string, it will return an IP address.
 *   - first it tries to convert the string directly
 *   - if that fails, it tries o resolve it as a hostname
 *
 * WARNING: gethostbyname() is a blocking function
 */
unsigned int getAddr ( const char *szHost) 
{
    struct hostent * lpstHost;
    u_long lAddr = INADDR_ANY;


	/* check that we have a string */
	if (*szHost) 
	{
		/* check for a dotted-IP address string */
		lAddr = inet_addr(szHost);
	}

	return (lAddr); 
}

void FormatTime2Str(time_t time1, char* szTime)
{
	struct tm tm1;

#ifdef WIN32
	tm1 = *localtime(&time1);
#else
	localtime_r(&time1, &tm1);
#endif
	sprintf(szTime, "%4.4d-%2.2d-%2.2d %2.2d:%2.2d:%2.2d", tm1.tm_year + 1900,
		tm1.tm_mon + 1, tm1.tm_mday, tm1.tm_hour, tm1.tm_min, tm1.tm_sec);
}

time_t FormatStr2Time(char* szTime)
{
	struct tm tm1; 

	sscanf(szTime, "%4d-%2d-%2d %2d:%2d:%2d", &tm1.tm_year, &tm1.tm_mon,
		&tm1.tm_mday, &tm1.tm_hour, &tm1.tm_min, &tm1.tm_sec); 

	tm1.tm_year -= 1900; 
	tm1.tm_mon --; 

	tm1.tm_isdst = -1; 

	return mktime(&tm1);
}

