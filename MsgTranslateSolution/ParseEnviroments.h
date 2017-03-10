#pragma once
#include "tinystr.h"
#include "tinyxml.h"
#include "Macro_Global.h"

class ParseEnviroments {
public:
	ParseEnviroments();
	virtual ~ParseEnviroments();
	// 额外的初始化步骤
	virtual int initself(const char* const parseBasePath);


	virtual TiXmlElement* GetParseRuleCollect();
	virtual TiXmlElement* GetPatternCollect();
	virtual TiXmlElement* GetLibraryCollect();
	virtual TiXmlElement* GetCmdPointCollect();


private:
	TiXmlDocument* docNode;
	// 存储用到的pattern集合节点
	TiXmlElement* patternCollect;
	// 存储常用的解析规则集合节点
	TiXmlElement* parseRuleCollect;
	TiXmlElement* CmdListNode;
	TiXmlElement* libraryCollectNode;
};

