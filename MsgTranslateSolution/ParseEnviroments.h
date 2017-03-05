#pragma once
#include "tinystr.h"
#include "tinyxml.h"
#include "Macro_Global.h"

class ParseEnviroments {
public:
	ParseEnviroments();
	virtual ~ParseEnviroments();
	// 载入解析依据文档
	virtual int LoadParseBase(const char* const parseBaseDoc);
	// 额外的初始化步骤
	virtual int initself();
	virtual int GetParseRuleCollect(TiXmlElement** elementRefOut);
	virtual int GetPatternCollect(TiXmlElement** elementRefOut);
	virtual int SetOriginalMsg(UWORD_i16* msg_in);
	virtual int GetOriginalMsg(UWORD_i16** msg_out);
	virtual int SetPureMsg(UWORD_i16* msg_in);
	virtual int GetPureMsg(UWORD_i16** msg_out);
private:
	TiXmlDocument* doc;
};

