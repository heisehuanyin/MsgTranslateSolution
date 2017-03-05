#pragma once
#include "tinystr.h"
#include "tinyxml.h"
#include "Macro_Global.h"

class ParseEnviroments {
public:
	ParseEnviroments();
	virtual ~ParseEnviroments();
	// ������������ĵ�
	virtual int LoadParseBase(const char* const parseBaseDoc);
	// ����ĳ�ʼ������
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

