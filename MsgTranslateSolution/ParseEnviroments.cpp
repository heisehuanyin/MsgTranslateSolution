#include "ParseEnviroments.h"



ParseEnviroments::ParseEnviroments() :
docNode(NULL)
, patternCollect(NULL)
, parseRuleCollect(NULL)
, CmdListNode(NULL)
, libraryCollectNode(NULL)
{}


ParseEnviroments::~ParseEnviroments() {}




// ³õÊ¼»¯²½Öè
int ParseEnviroments::initself(const char* const parseBasePath) {
	this->docNode = new TiXmlDocument(parseBasePath);
	this->docNode->LoadFile(TIXML_ENCODING_LEGACY);


	TiXmlElement* protocolNode = this->docNode->FirstChildElement("protocol");
	TiXmlElement* sysCfg = protocolNode->FirstChildElement("sysConfig");
	this->libraryCollectNode = sysCfg->FirstChildElement("library");
	this->CmdListNode = sysCfg->FirstChildElement("cmdlist");
	this->patternCollect = sysCfg->FirstChildElement("pattern");
	this->parseRuleCollect = protocolNode->FirstChildElement("parseRule");




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
