#define STDINTERFACE_EXPORTS 1

#include "stdafx.h"
#include "targetver.h"
#include "Card_57_original_msg_parse_support.h"
#include "../MsgTranslateSolution/Macro_Global.h"
#include <stdio.h>


Card57_parse_support::Card57_parse_support()
{
	this->KeyWordsArray[0] = "RTADDR";
	this->KeyWordsArray[1] = "SUBADDR";
	this->KeyWordsArray[2] = "MTSTATE";
	this->KeyWordsArray[3] = "RTSTATE";
	this->KeyWordsArray[4] = "MSGLENGTH";
	this->KeyWordsArray[5] = "SYSTIME";
	this->KeyWordsArray[6] = "B1553TIME";
	this->KeyWordsArray[7] = "MSGTYPE";
	this->KeyWordsArray[8] = "RTADDR_E";
	this->KeyWordsArray[9] = "SUBADDR_E";
	this->KeyWordsArray[10]= "RTSTATE_E";
	this->KeyWordsArray[11] = "MSGCOUNT";
}


Card57_parse_support::~Card57_parse_support()
{
}


int Card57_parse_support::GetKeyWords(const UWORD_i16* const msgArray, const char* const argv, char** bufferOut)
{
	//消息类别标示码：0,未知;		1,RT->BC;	2,BC->RT;	3,RT->RT;	4,矢量字;
	int msgType = 0;

	// 帧头		 帧计数		  系统时标	MT		1553B时标
	// aa55 aa55 | 0100 0000 | 29b6 0000| 0081 | 3979
	if (!strcmp(argv,"MSGCOUNT"))
	{
		int tmp = this->MSGCount(msgArray);
	}
	return 0;
}


int Card57_parse_support::EnumKeyWordsInner(char*** argsArrayOut, int* argsCount)
{
	*argsArrayOut = this->KeyWordsArray;

	*argsCount = 12;

	return 0;
}


int Card57_parse_support::GetPureMsgBody(const UWORD_i16* const msgBufin, UWORD_i16* bufferOut)
{
	return 0;
}


StandardParseBaseSupportInterface* GetNewParseBaseInstancePtr(char** argv, int argc ) {
	return new Card57_parse_support();
}

// 通过此函数返回消息的类别，返回值是消息的类别
int Card57_parse_support::GetMsgType(const UWORD_i16* const ArrayIn)
{


	return 0;
}


// 翻转一个十六位数字的高低八位
int Card57_parse_support::Reversal(const UWORD_i16* const oneWord)
{
	int temp = (*oneWord >> 8) & 0xff;

	return ((*oneWord & 0xff) << 8) | temp;
}


int Card57_parse_support::MSGCount(const UWORD_i16* const msgArray)
{
	int trmp = 0;
	trmp = this->Reversal(msgArray + 2);
	return (this->Reversal(msgArray + 3) << 16) & 0xffff0000 | trmp;
}
