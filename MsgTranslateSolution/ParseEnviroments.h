#pragma once
#include "tinystr.h"
#include "tinyxml.h"
#include "Macro_Global.h"
#include "AbstractPlugClass.h"
#include <string>
#include <map>
#include "StandardParseBaseSupportInterface.h"
#include "StandardExtensionInterface.h"
#include "ExtensionLoader.h"
#include "CmdWrapper.h"


class ParseEnviroments {
public:
	ParseEnviroments();
	virtual ~ParseEnviroments();
	// 额外的初始化步骤
	virtual int initself(const char* const parseBasePath, const char* const binaryFilePath);


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
	// 存储常用的命令点
	TiXmlElement* CmdListNode;
	// 存储常用的库集
	TiXmlElement* libraryCollectNode;
public:
	virtual StandardBaseSupportInterface* GetBaseSupportPlug();
	virtual AbstractPlugClass* GetUniversalPlugin(const char* const pluginName);
private:
	std::map<std::string, AbstractPlugClass*> pluginContainer;
	ExtensionLoader* LoadManager;
	StandardBaseSupportInterface* baseSupport;
public:
	virtual CmdWrapper* GetCmdConfig(const char* const cmdName);
private:
	std::map<std::string, CmdWrapper*> ConfigContainer;
};

