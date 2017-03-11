#include "ParseEnviroments.h"

using namespace std;



ParseEnviroments::ParseEnviroments() :
docNode(NULL)
, patternCollect(NULL)
, parseRuleCollect(NULL)
, CmdListNode(NULL)
, libraryCollectNode(NULL)
, LoadManager(NULL)
{
	this->LoadManager = new ExtensionLoader();
}


ParseEnviroments::~ParseEnviroments() {}




// 初始化步骤
int ParseEnviroments::initself(const char* const parseBasePath, const char* const binaryFilePath) {
	this->docNode = new TiXmlDocument(parseBasePath);
	this->docNode->LoadFile(TIXML_ENCODING_LEGACY);





	TiXmlElement* protocolNode = this->docNode->FirstChildElement("protocol");
	TiXmlElement* sysCfg = protocolNode->FirstChildElement("sysConfig");
	this->libraryCollectNode = sysCfg->FirstChildElement("library");
	this->CmdListNode = sysCfg->FirstChildElement("cmdlist");
	this->patternCollect = sysCfg->FirstChildElement("pattern");
	this->parseRuleCollect = protocolNode->FirstChildElement("parseRule");





	//寻找合适节点====================================================
	TiXmlElement* baseSupport = this->GetLibraryCollect()->FirstChildElement("baseSupport");

	// loadBasePlug===================================================
	char** ab = (char**)&"";
	int ntemp = 0;
	StandardBaseSupportInterface* basep = nullptr;
	this->LoadManager->LoadNewParseBaseExtension(baseSupport->Attribute("rel"), ab, ntemp, &basep);

	//open binary data file
	if (binaryFilePath != NULL) {
		basep->OpenBinaryDataFile(binaryFilePath);
	}
	this->baseSupport = basep;
	this->pluginContainer.insert(make_pair(baseSupport->Attribute("rel"), basep));
	






	// loadEnhancePlug================================================
	StandardExtensionInterface* pextension = NULL;
	TiXmlElement* elm = this->GetLibraryCollect()->FirstChildElement("enhance");
	while (elm != NULL) {
		//正式工作
		this->LoadManager->LoadNewParseEnhanceExtension(elm->Attribute("rel"), ab, ntemp, &pextension);
		this->pluginContainer.insert(make_pair(elm->Attribute("rel"), pextension));

		elm = elm->NextSiblingElement();
	}



	TiXmlElement* cmdOne = this->GetCmdPointCollect()->FirstChildElement();
	while (cmdOne != NULL) {
		string keyandargs = cmdOne->Attribute("rel");
		CmdWrapper* group = new CmdWrapper();
		char teep[1024] = "";
		sprintf_s(teep, "%s", keyandargs.c_str());

		group->initSelf(teep);

		//collect cmdRel items
		this->ConfigContainer.insert(make_pair(cmdOne->Value(), group));

		cmdOne = cmdOne->NextSiblingElement();
	}

	return 0;
}


TiXmlElement* ParseEnviroments::GetParseRuleCollect() {
	return this->parseRuleCollect;
}


TiXmlElement* ParseEnviroments::GetPatternCollect() {
	return this->patternCollect;
}



TiXmlElement* ParseEnviroments::GetLibraryCollect()
{
	return this->libraryCollectNode;
}


TiXmlElement* ParseEnviroments::GetCmdPointCollect()
{
	return this->CmdListNode;
}


StandardBaseSupportInterface* ParseEnviroments::GetBaseSupportPlug()
{
	return this->baseSupport;
}


AbstractPlugClass* ParseEnviroments::GetUniversalPlugin(const char* const pluginName)
{
	string key = pluginName;
	map<string, AbstractPlugClass*>::iterator end = this->pluginContainer.end();
	map<string, AbstractPlugClass*>::iterator it = this->pluginContainer.find(key);

	if (it != end) {
		return it->second;
	}

	return nullptr;
}


CmdWrapper* ParseEnviroments::GetCmdConfig(const char* const cmdName)
{
	return this->ConfigContainer[cmdName];
}
