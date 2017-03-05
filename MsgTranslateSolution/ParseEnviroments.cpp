#include "ParseEnviroments.h"



ParseEnviroments::ParseEnviroments() : doc(NULL) {}


ParseEnviroments::~ParseEnviroments() {}


// 载入解析依据文档
int ParseEnviroments::LoadParseBase(const char* const parseBaseDoc) {
	//基于xml解析，建立载入点
	this->doc = new TiXmlDocument();//一个文档节点
	doc->LoadFile(parseBaseDoc);

	return 0;
}


// 额外的初始化步骤
int ParseEnviroments::initself() {
	return 0;
}


int ParseEnviroments::GetParseRuleCollect(TiXmlElement** elementRefOut) {
	return 0;
}


int ParseEnviroments::GetPatternCollect(TiXmlElement** elementRefOut) {
	return 0;
}


int ParseEnviroments::SetOriginalMsg(UWORD_i16* msg_in) {
	return 0;
}


int ParseEnviroments::GetOriginalMsg(UWORD_i16** msg_out) {
	return 0;
}


int ParseEnviroments::SetPureMsg(UWORD_i16* msg_in) {
	return 0;
}


int ParseEnviroments::GetPureMsg(UWORD_i16** msg_out) {
	return 0;
}
