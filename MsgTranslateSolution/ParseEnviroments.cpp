#include "ParseEnviroments.h"



ParseEnviroments::ParseEnviroments() : docNode(NULL) {}


ParseEnviroments::~ParseEnviroments() {}


// ������������ĵ�
int ParseEnviroments::LoadParseBase(const char* const parseBaseDoc) {
	//����xml���������������
	this->docNode = new TiXmlDocument();//һ���ĵ��ڵ�
	docNode->LoadFile(parseBaseDoc);

	return 0;
}


// ����ĳ�ʼ������
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
