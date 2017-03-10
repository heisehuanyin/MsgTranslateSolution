#include "stdafx.h"
#include "targetver.h"
#include "Card_57_original_msg_parse_support.h"
#include "../MsgTranslateSolution/Macro_Global.h"
#include <stdio.h>
#include <stdlib.h>


CardXX_parse_support::CardXX_parse_support()
	: binaryFile(NULL) {
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
	this->binaryFile = new DataFileAccess();
}


CardXX_parse_support::~CardXX_parse_support()
{
	delete this->binaryFile;
}


int CardXX_parse_support::ProcessMsgUnitAsHexOrStr(const UWORD_i16* const msgArray, const char* const argv, char** bufferOut)
{
	//消息类别标示码：0,未知;		1,RT->BC;	2,BC->RT;	3,RT->RT;	4,矢量字;
	int vvv = *(msgArray + 9);
	int msgType = 0;

	int msgLength = 0;//消息长度
	int temp = vvv & 0x1f;

	if (temp == 0) {
		msgLength = 0x20;
	}
	else {
		msgLength = temp;
	}
	//获取消息长度
	if (!strcmp(argv, this->KeyWordsArray[4])) {
		sprintf_s(this->content, 2048, "%x", msgLength);
		*bufferOut = this->content;
		return 0;
	}


	temp = (vvv >> 5)& 0xf;//抽取第一个命令字中的子地址
	int subAddr = temp;

	temp = (vvv >> 9) & 0x03;//数据流向
	if (temp == 0)//B->R
	{
		//之前都在解析命令字2，现在获取命令字1
		int cmd1 = *(msgArray + 10);
		int cmd1temp = (cmd1 >> 9) & 0x03;
		if (cmd1temp != temp && (cmd1 & 0x1f) == (vvv & 0x1f)) {
			int numcalc = *(msgArray + 11 + msgLength);
			int rtzt2 = *(msgArray + 12 + msgLength);
			if ((numcalc == 0x0 && rtzt2 == 0x0) || (numcalc == 0xaa55 && rtzt2 == 0xaa55)) {
				msgType = 2;
			}
			else {
				msgType = 3;
			}
		}
		else {
			msgType = 2;
		}
	}
	else {
		//R->B
		if (subAddr == 0) {
			msgType = 4;
		}
		else {
			msgType = 1;
		}
	}
	//返回消息类型
	if (!strcmp(argv, this->KeyWordsArray[7])) {
		sprintf_s(this->content, 2048, "%x", msgType);
		*bufferOut = this->content;
		return 0;
	}
	
	
	
	//返回消息计数：
	if (!strcmp(argv, this->KeyWordsArray[11])) {
		long tws = 0;
		int mtemp = *(msgArray + 2);
		tws = mtemp;
		mtemp = *(msgArray + 3);
		tws += (mtemp << 16);
		sprintf_s(this->content, 2048, "%x", tws);

		*bufferOut = this->content;
		return 0;
	}



	//1553B时标
	if (!strcmp(argv, this->KeyWordsArray[6])) {
		int mtemp = *(msgArray + 7);
		sprintf_s(this->content, 2048, "%x", mtemp);

		*bufferOut = this->content;
		return 0;
	}
	
	
	
	//系统时标
	if (!strcmp(argv, this->KeyWordsArray[5])) {
		long tws = 0;
		int mtemp = *(msgArray + 4);
		tws = mtemp;
		mtemp = *(msgArray + 5);
		tws += (mtemp << 16);
		sprintf_s(this->content, 2048, "%x", tws);

		*bufferOut = this->content;
		return 0;
	}
	
	
	
	//MT状态字
	if (!strcmp(argv, this->KeyWordsArray[2])) {
		int mtemp = *(msgArray + 6);
		sprintf_s(this->content, 2048, "%x", mtemp);

		*bufferOut = this->content;
		return 0;
	}
	
	
	

	//RTADDR
	if (!strcmp(argv, this->KeyWordsArray[0])) {
		int rtaddr = 0;

		if (msgType == 3) {
			rtaddr = (*(msgArray + 10) >> 0x0b) & 0x1f;
		}
		else {
			rtaddr = (*(msgArray + 9) >> 0x0b) & 0x1f;
		}

		sprintf_s(this->content, 2048, "%x", rtaddr);
		*bufferOut = this->content;
		return 0;
	}



	//RTADDR_E
	if (!strcmp(argv, this->KeyWordsArray[8]) && msgType == 3) {
		int mtemp = *(msgArray + 9);
		sprintf_s(this->content, 2048, "%x", (mtemp >> 11) & 0x1f);
		*bufferOut = this->content;
		return 0;
	}
	else if(!strcmp(argv, this->KeyWordsArray[8])){
		sprintf_s(this->content, 2048, "N/A");
		*bufferOut = this->content;
		return -1;
	}



	//返回子地址
	if (!strcmp(argv, this->KeyWordsArray[1])) {
		if (msgType == 3) {
			subAddr = (*(msgArray + 10) >> 5) & 0x0f;
		}
		sprintf_s(this->content, 2048, "%x", subAddr);
		*bufferOut = this->content;
		return 0;
	}
	



	//SUBADDR_E
	if (!strcmp(argv, this->KeyWordsArray[9]) && msgType == 3) {
		int mtemp = *(msgArray + 9);
		sprintf_s(this->content, 2048, "%x", (mtemp >> 5) & 0x0f);
		*bufferOut = this->content;
		return 0;
	}
	else if(!strcmp(argv, this->KeyWordsArray[9])){
		sprintf_s(this->content, 2048, "N/A");
		*bufferOut = this->content;
		return -1;
	}


	//RT状态字
	if (!strcmp(argv, this->KeyWordsArray[3])) {
		int mtemp = 0;
		if (msgType == 1 || msgType == 4) {
			mtemp = *(msgArray + 10);
		}
		else if (msgType == 2) {
			mtemp = *(msgArray + 10 + msgLength);
		}
		else if (msgType == 3) {
			mtemp = *(msgArray + 11);
		}

		sprintf_s(this->content, 2048, "%x", mtemp);
		*bufferOut = this->content;
		return 0;
	}



	//RTSTATE_E
	if (!strcmp(argv, this->KeyWordsArray[10]) && msgType == 3) {
		int mtemp = *(msgArray + 7);
		sprintf_s(this->content, 2048, "%x", mtemp);
		*bufferOut = this->content;
		return 0;
	}
	else if(!strcmp(argv, this->KeyWordsArray[10])){
		sprintf_s(this->content, 2048, "N/A");
		*bufferOut = this->content;
		return -1;
	}



	


	return 0;
}


int CardXX_parse_support::EnumKeyWordsInner(char*** argsArrayOut, int* argsCount)
{
	*argsArrayOut = this->KeyWordsArray;

	*argsCount = 12;

	return 0;
}


int CardXX_parse_support::GetPureMsgBody(UWORD_i16 * const msgBufin, UWORD_i16 ** bufferOut)
{
	char *temp = "存储函数类型的内容，长度应该够用了";

	this->ProcessMsgUnitAsHexOrStr(msgBufin, "MSGTYPE", &temp);
	//消息类别标示码：0,未知;		1,RT->BC;	2,BC->RT;	3,RT->RT;	4,矢量字;

	int type = atoi(temp);

	switch (type) {
		case 1:
			*bufferOut = msgBufin + 11;
			break;
		case 2:
			*bufferOut = msgBufin + 10;
			break;
		case 3:
			*bufferOut = msgBufin + 12;
			break;
		case 4:
			*bufferOut = msgBufin + 11;
			break;
		default:
			break;
	}

	return 0;
}


StandardParseBaseSupportInterface* GetNewParseBaseInstancePtr(char** argv, int argc ) {
	return new CardXX_parse_support();
}



int CardXX_parse_support::GetOneOriginalMsg(UWORD_i16** bufferOut)
{
	return this->binaryFile->GetAMsgFromDataFile(bufferOut);
}


int CardXX_parse_support::OpenBinaryDataFile(const char* const filePath)
{
	this->binaryFile->initSelf(filePath);
	return 0;
}
