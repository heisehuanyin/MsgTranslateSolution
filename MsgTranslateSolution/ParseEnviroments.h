#pragma once
#include "tinystr.h"
#include "tinyxml.h"
#include "Macro_Global.h"

class ParseEnviroments {
public:
	ParseEnviroments();
	virtual ~ParseEnviroments();
	// ����ĳ�ʼ������
	virtual int initself(const char* const parseBasePath);


	virtual TiXmlElement* GetParseRuleCollect();
	virtual TiXmlElement* GetPatternCollect();
	virtual TiXmlElement* GetLibraryCollect();
	virtual TiXmlElement* GetCmdPointCollect();


private:
	TiXmlDocument* docNode;
	// �洢�õ���pattern���Ͻڵ�
	TiXmlElement* patternCollect;
	// �洢���õĽ������򼯺Ͻڵ�
	TiXmlElement* parseRuleCollect;
	TiXmlElement* CmdListNode;
	TiXmlElement* libraryCollectNode;
};

