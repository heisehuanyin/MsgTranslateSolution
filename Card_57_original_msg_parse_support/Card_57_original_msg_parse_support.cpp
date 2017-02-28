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
	this->KeyWordsArray[11] = "MSGCOUNT";//消息计数
}


Card57_parse_support::~Card57_parse_support()
{
}


int Card57_parse_support::GetKeyWords(const UWORD_i16* const msgArray, const char* const argv, char** bufferOut)
{
	//消息类别标示码：0,未知;		1,RT->BC;	2,BC->RT;	3,RT->RT;	4,矢量字;
	int msgType = 0;
	int msgLength = 0;//消息长度

	int vvv = this->Reversal(msgArray + 9);
	int temp = vvv & 0x1f;
	
	if (temp == 0)
	{
		msgLength = 0x20;
	}
	else
	{
		msgLength = temp;
	}
	if (!strcmp(argv,this->KeyWordsArray[4]))
	{
		sprintf_s(*bufferOut, 10, "%d", msgLength);
		return 0;
	}
	vvv = vvv >> 5;

	temp = vvv & 0x0f;//子地址
	int subAddr = temp;
	if (!strcmp(argv, this->KeyWordsArray[1]))
	{
		sprintf_s(*bufferOut, 10, "%d", subAddr);
		return 0;
	}
	vvv = vvv >> 4;

	temp = vvv & 0x03;//消息类型
	if (temp == 0)//B->R
	{
		//
		int cmd1 = this->Reversal(msgArray + 10);
		int cmd1temp = (cmd1 >> 9) & 0x03;
		if (cmd1temp == temp && (cmd1 & 0x1f) == (vvv & 0x1f))
		{
			int numcalc = *(msgArray + 11 + msgLength);
			int rtzt2 = *(msgArray + 12 + msgLength);
			if ((numcalc == 0x0 && rtzt2 == 0x0) || (numcalc == 0xaa55 && rtzt2 == 0xaa55))
			{
				msgType = 2;
			}
			else
			{
				msgType = 3;
			}
		}
		else
		{
			msgType = 2;
		}
	}
	else {
		//R->B
		if (subAddr == 0)
		{
			msgType = 4;
		}
		else
		{
			msgType = 1;
		}
	}
	if (!strcmp(argv, this->KeyWordsArray[7]))
	{
		sprintf_s(*bufferOut, 10, "%d", msgType);
		return 0;
	}
	vvv = vvv >> 2;


	temp = vvv & 0x1f;
	int rtaddr = temp; //RT地址
	if (!strcmp(argv, this->KeyWordsArray[0]))
	{
		sprintf_s(*bufferOut, 10, "%d", rtaddr);
		return 0;
	}

	//MTSTATE
	if (!strcmp(argv, this->KeyWordsArray[2]))
	{
		int mtemp = this->Reversal(msgArray + 6);
		sprintf_s(*bufferOut, 10, "%x", mtemp);
		return 0;
	}

	//RTSTATE
	if (!strcmp(argv, this->KeyWordsArray[3]))
	{
		int mtemp = 0;
		if (msgType == 1 || msgType == 4)
		{
			mtemp = this->Reversal(msgArray + 10);
		}
		else if (msgType == 2)
		{
			mtemp = this->Reversal(msgArray + 10 + msgLength);
		}
		else if (msgType == 3)
		{
			mtemp = this->Reversal(msgArray + 11);
		}

		sprintf_s(*bufferOut, 10, "%x", mtemp);
		return 0;
	}

	//SYSTIME
	if (!strcmp(argv, this->KeyWordsArray[5]))
	{
		char temppp[20] = "";
		int mtemp = this->Reversal(msgArray + 4);
		sprintf_s(temppp, 10, "%x", mtemp);
		mtemp = this->Reversal(msgArray + 5);
		sprintf_s(*bufferOut, 10, "%x%s", mtemp,temppp);
		return 0;
	}
	//B1553BTIME 6
	if (!strcmp(argv, this->KeyWordsArray[6]))
	{
		int mtemp = this->Reversal(msgArray + 7);
		sprintf_s(*bufferOut, 10, "%x", mtemp);
		return 0;
	}
	//MSGCOUNT
	if (!strcmp(argv, this->KeyWordsArray[11]))
	{
		char temppp[20] = "";
		int mtemp = this->Reversal(msgArray + 2);
		sprintf_s(temppp, 10, "%x", mtemp);
		mtemp = this->Reversal(msgArray + 3);
		sprintf_s(*bufferOut, 10, "%x%s", mtemp, temppp);
		return 0;
	}
	//RTADDR_E
	if (!strcmp(argv, this->KeyWordsArray[8]) && msgType == 3)
	{
		int mtemp = this->Reversal(msgArray + 9);
		sprintf_s(*bufferOut, 10, "%x", (mtemp >> 11)& 0x1f);
		return 0;
	}
	else {
		sprintf_s(*bufferOut, 10, "N/A");
		return -1;
	}
	//SUBADDR_E
	if (!strcmp(argv, this->KeyWordsArray[9]) && msgType == 3)
	{
		int mtemp = this->Reversal(msgArray + 9);
		sprintf_s(*bufferOut, 10, "%x", (mtemp >> 5) & 0x0f);
		return 0;
	}
	else {
		sprintf_s(*bufferOut, 10, "N/A");
		return -1;
	}
	//RTSTATE_E
	if (!strcmp(argv, this->KeyWordsArray[10]) && msgType == 3)
	{
		int mtemp = this->Reversal(msgArray + 7);
		sprintf_s(*bufferOut, 10, "%x", mtemp);
		return 0;
	}
	else {
		sprintf_s(*bufferOut, 10, "N/A");
		return -1;
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



// 翻转一个十六位数字的高低八位
int Card57_parse_support::Reversal(const UWORD_i16* const oneWord)
{
	int temp = (*oneWord >> 8) & 0xff;

	return ((*oneWord & 0xff) << 8) | temp;
}
