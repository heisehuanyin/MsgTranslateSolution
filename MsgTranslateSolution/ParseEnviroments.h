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
	// ����ĳ�ʼ������
	virtual int initself(const char* const parseBasePath, const char* const binaryFilePath);


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
	// �洢���õ������
	TiXmlElement* CmdListNode;
	// �洢���õĿ⼯
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

