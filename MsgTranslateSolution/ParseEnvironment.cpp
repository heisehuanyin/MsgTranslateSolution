#include "ParseEnvironment.h"


using namespace std;

ParseUnit::~ParseUnit() {}


ParseUnit::ParseUnit()
	: binaryFilePath(NULL)
	, StrictStr(NULL)
	, outputFilePtr(NULL)
	, OriginalMsgCache(NULL)
	, prsEnv(NULL), fitTimes(0) {
	
	this->prsEnv = new ParseEnviroments();
}


int ParseUnit::initSelf(const char* const parseBase, const char* const binaryDataFile, const char* const strictString, const char* const outputFile) {
	this->binaryFilePath = binaryDataFile;
	this->StrictStr = strictString;

	this->prsEnv->initself(parseBase, binaryDataFile);

	if (outputFile != NULL) {
		fopen_s(&this->outputFilePtr, outputFile, "w");
	}

	return 0;
}


int ParseUnit::SetOriginalMsg(UWORD_i16 * const OriginalMsg) {
	this->OriginalMsgCache = OriginalMsg;
	return 0;
}








int ParseUnit::GetOneMsg(UWORD_i16** original_msg) {
	if (this->binaryFilePath == NULL) {
		if (this->OriginalMsgCache == NULL) {
			return -1;
		}
		*original_msg = this->OriginalMsgCache;
		this->OriginalMsgCache = NULL;
	}
	else {
		return this->prsEnv->GetBaseSupportPlug()->GetOneOriginalMsg(original_msg);
	}
	return 0;
}


bool ParseUnit::CheckCriterion(const char* const tagName, const char* const Msgindex, const char* const valCertain, UWORD_i16 * const msg_in) {
	
	if (!strcmp(valCertain,"not")) {
		return true;
	}
	CmdWrapper* tmpWrap = this->prsEnv->GetCmdConfig(tagName);
	char* val = "";

	AbstractPlugClass* plugin = this->prsEnv->GetUniversalPlugin(tmpWrap->linkRel);

	if (!strcmp(Msgindex,"not")) {
		plugin->ProcessMsgUnitAsHexOrStr(msg_in, tmpWrap->arguments, &val);
	}
	else {
		int index = atoi(Msgindex);
		UWORD_i16* puremsg = nullptr;
		this->prsEnv->GetBaseSupportPlug()->GetPureMsgBody(msg_in, &puremsg);

		plugin->ProcessMsgUnitAsHexOrStr(puremsg+index, tmpWrap->arguments, &val);

	}
	int valpre = strtol(valCertain, NULL, 16);
	int valafter = strtol(val, NULL, 16);
	if (valpre == valafter) {
		return true;
	}
	
	return false;
}


int ParseUnit::ProcPureMsgSection(TiXmlElement * pureMsgRuleCollect, UWORD_i16 * const puremsg_in) {
	TiXmlElement* oneParseRule = pureMsgRuleCollect->FirstChildElement();

	while (oneParseRule != NULL) {
		const char* tag_name = oneParseRule->Value();
		const char* v_index = oneParseRule->Attribute("index");
		const char* v_name = oneParseRule->Attribute("name");

		int v_i = atoi(v_index);
		char* val = "";
		if (!strcmp(v_name, "default")) {
			v_name = tag_name;
		}
		
		CmdWrapper* tmpit = this->prsEnv->GetCmdConfig(tag_name);
		AbstractPlugClass* plugin = this->prsEnv->GetUniversalPlugin(tmpit->linkRel);

		plugin->ProcessMsgUnitAsHexOrStr(puremsg_in + v_i, tmpit->arguments, &val);

		if (this->outputFilePtr == NULL) {
			printf("%s:%s\t", v_name , val);
		}
		else {
			fprintf_s(this->outputFilePtr, "%s:%s\t", v_name, val);
		}

		oneParseRule = oneParseRule->NextSiblingElement();
	}

	if (this->outputFilePtr == NULL) {
		printf("\n\n");
	}
	else {
		fprintf_s(this->outputFilePtr, "\n\n");
	}

	return 0;
}


int ParseUnit::MsgBasicParse(const UWORD_i16* const msg_in) {
	char** keywords = nullptr;
	int num = 0;

	this->prsEnv->GetBaseSupportPlug()->EnumKeyWordsInner(&keywords, &num);

	char* value = nullptr;
	for (int i = 0; i < num; i++) {
		this->prsEnv->GetBaseSupportPlug()->ProcessMsgUnitAsHexOrStr(msg_in, *(keywords + i), &value);
		
		if (this->outputFilePtr == NULL) {
			printf("%s:%s\t", *(keywords + i), value);
		}
		else {
			fprintf_s(this->outputFilePtr, "%s:%s\t", *(keywords + i), value);
		}
	}
	

	return 0;
}


int ParseUnit::translateMsgAtNow() {
	UWORD_i16 * msg_out;

	while (this->GetOneMsg(&msg_out) != -1) {
		this->MsgBasicParse(msg_out);
		this->fitTimes = 0;//重置统计标志量
		this->FindRuleAdaptAndTranslate(this->prsEnv->GetPatternCollect(), this->prsEnv->GetParseRuleCollect(), msg_out);
		if (this->fitTimes != 1) {
			printf("\n解析失败，未发现适配的解析规则(0)或者多次适配，解析规则存在歧义(>1)，适配次数:%d\n\n",  this->fitTimes);
		}
	}
	return 0;
}


int ParseUnit::FindRuleAdaptAndTranslate(TiXmlElement* patternCollect, TiXmlElement* parseRuleCollect, UWORD_i16 * const msg_in) {
	TiXmlElement* elelm = patternCollect->FirstChildElement();
	const char* tagname = elelm->Value();

	while (elelm != NULL) {
		const char* varIndex = elelm->Attribute("index");
		TiXmlElement* oneRuleAdapted = parseRuleCollect->FirstChildElement();

		while (oneRuleAdapted != NULL) {
			const char* target_value = oneRuleAdapted->Attribute("value");

			if (this->CheckCriterion(tagname, varIndex, target_value, msg_in)) {
				if (elelm->NoChildren()) {
					UWORD_i16* puremsg = nullptr;
					this->prsEnv->GetBaseSupportPlug()->GetPureMsgBody(msg_in, &puremsg);
					this->ProcPureMsgSection(oneRuleAdapted, puremsg);
					this->fitTimes += 1;
				}
				else {
					this->FindRuleAdaptAndTranslate(elelm, oneRuleAdapted, msg_in);
				}
				if (this->fitTimes > 1) {
					printf("%s:第%d 次出现", elelm->Value(), this->fitTimes);
				}
			}
			oneRuleAdapted = oneRuleAdapted->NextSiblingElement();
		}
		elelm = elelm->NextSiblingElement();
	}

	return 0;
}

