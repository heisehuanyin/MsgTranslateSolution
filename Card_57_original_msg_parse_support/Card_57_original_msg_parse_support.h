﻿#pragma once

#include "../MsgTranslateSolution/StandardParseBaseSupportInterface.h"
#include "../MsgTranslateSolution/Macro_Global.h"
#include "DataFileAccess.h"



class CardXX_parse_support :
	public StandardBaseSupportInterface
{
public:
	CardXX_parse_support();
	virtual ~CardXX_parse_support();

	// 根据传入的二维字符串数组获取总线消息中的信息，通过bufferOut返回信息，参与到软件主体的判断过程
	// 输入参数：msgArray,传入的软件主体获取的原始总线消息。
	// 输入参数：argv，传入的字符串数组,存储传入的参数。
	// 输入参数：bufferOut,处理后得到的内容通过此缓存区传出。
	virtual int ProcessMsgUnitAsHexOrStr(const UWORD_i16* const msgArray, const char* const argv, char** bufferOut);

	// 提取基础解析服务模块所提供的所有消息解析方式
	// 输入参数：argsArrayOut,获取本模块提供的解析服务的所有方式
	// 输入参数：argsCount，方式数量
	virtual int EnumKeyWordsInner(char*** argsArrayOut, int* argsCount);

	//获取纯消息
	virtual int GetPureMsgBody(UWORD_i16 * const msgBufin, UWORD_i16 ** bufferOut);


private:
	char* KeyWordsArray[20];

public:
	int GetOneOriginalMsg(UWORD_i16** bufferOut);
	virtual int OpenBinaryDataFile(const char* const filePath);
private:
	char content[2048];
	DataFileAccess* binaryFile;
};
