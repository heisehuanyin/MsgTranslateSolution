#include "ParseEnvironment.h"


using namespace std;

ParseUnit::~ParseUnit() {}


ParseUnit::ParseUnit()
	: binaryFilePath(NULL)
	, StrictStr(NULL)
	, PureMsg(NULL), doc(NULL)
	, loadTools(NULL)
	, basep(NULL)
	, outputFilePtr(NULL)
	, OriginalMsgCache(NULL)
	, patternCollect(NULL)
	, parseRuleCollect(NULL), prsEnv(NULL), fitTimes(0) {}


int ParseUnit::initSelf(const char* const parseBase, const char* const binaryDataFile, const char* const strictString, const char* const outputFile) {
	this->binaryFilePath = binaryDataFile;
	this->StrictStr = strictString;

	this->doc = new TiXmlDocument(parseBase);
	this->doc->LoadFile(TIXML_ENCODING_LEGACY);

	//创建插件加载器
	this->loadTools = new ExtensionLoader();
	this->LoadParseLibrary();
	this->LoadCmdEnterPoint();
	this->LoadPatternAndParseRule();


	if (outputFile != NULL) {
		fopen_s(&this->outputFilePtr, outputFile, "w");
	}

	return 0;
}


int ParseUnit::SetOriginalMsg(UWORD_i16 * const OriginalMsg) {
	this->OriginalMsgCache = OriginalMsg;
	return 0;
}



int ParseUnit::CollectCmdEnterPoint(const char* const CmdName, const char* const libraryKeyAndArgs) {
	string key = CmdName;
	string value = libraryKeyAndArgs;
	this->cmdEnterpointContainer[key] = value;
	
	return 0;
}


int ParseUnit::LoadParseLibrary() {

	//寻找合适节点====================================================
	TiXmlElement* protocolNode = this->doc->FirstChildElement("protocol");
	TiXmlElement* sysCfg = protocolNode->FirstChildElement("sysConfig");
	TiXmlElement* library = sysCfg->FirstChildElement("library");
	TiXmlElement* baseSupport = library->FirstChildElement("baseSupport");

	// loadBasePlug===================================================
	char** ab = (char**)&"";
	int ntemp = 0;


	this->loadTools->LoadNewParseBaseExtension(baseSupport->Attribute("rel"), ab, ntemp, &this->basep);
	
	//open binary data file
	if (this->binaryFilePath != NULL) {
		basep->OpenBinaryDataFile(this->binaryFilePath);
	}

	this->CollectPlugIn(baseSupport->Attribute("rel"), basep);


	// loadEnhancePlug================================================
	StandardExtensionInterface* pextension = NULL;
	TiXmlElement* elm = library->FirstChildElement("enhance");
	while (elm != NULL) {
		//正式工作
		this->loadTools->LoadNewParseEnhanceExtension(elm->Attribute("rel"), ab, ntemp, &pextension);

		this->CollectPlugIn(elm->Attribute("rel"), pextension);

		elm = elm->NextSiblingElement();
	}

	return 0;
}


AbstractPlugClass* ParseUnit::GetPlugWrapper(const char * const PlugName) {
	string key = PlugName;
	map<string, AbstractPlugClass*>::iterator it = this->wrapperContainer.end();

	if (this->wrapperContainer.find(key) != it) {
		return it->second;
	}

	return nullptr;
}


int ParseUnit::LoadCmdEnterPoint() {

	TiXmlElement* sysCfg = this->doc->FirstChildElement("protocol")->FirstChildElement("sysConfig");
	TiXmlElement* cmdList = sysCfg->FirstChildElement("cmdlist");
	TiXmlElement* cmdOne = cmdList->FirstChildElement();
	while (cmdOne != NULL) {
		char cmdandrel[2048] = "";
		sprintf_s(cmdandrel, 2000, "%s", cmdOne->Attribute("rel"));
		char* cmd = nullptr;
		char* cmdtemp = nullptr;
		cmd = strtok_s(cmdandrel, " ", &cmdtemp);
		this->CollectCmdEnterPoint(cmdOne->Value(), cmdOne->Attribute("rel"));


		cmdOne = cmdOne->NextSiblingElement();
	}
	return 0;
}


int ParseUnit::LoadPatternAndParseRule() {

	TiXmlElement* sysCfg = this->doc->FirstChildElement("protocol")->FirstChildElement("sysConfig");
	this->patternCollect = sysCfg->FirstChildElement("pattern");
	this->parseRuleCollect = doc->FirstChildElement("protocol")->FirstChildElement("parseRule");

	return 0;
}


int ParseUnit::GetMsgFromCache(UWORD_i16** original_msg) {
	if (this->binaryFilePath == NULL) {
		if (this->OriginalMsgCache == NULL) {
			return -1;
		}
		*original_msg = this->OriginalMsgCache;
		this->OriginalMsgCache = NULL;
	}
	else {
		return this->basep->GetOneOriginalMsg(original_msg);
	}
	return 0;
}


bool ParseUnit::CheckCriterion(const char* const tagName, const char* const Msgindex, const char* const valCertain, UWORD_i16 * const msg_in) {
	
	if (!strcmp(valCertain,"not")) {
		return true;
	}

	string keyandargs = this->cmdEnterpointContainer[tagName];
	string key = keyandargs.substr(0, keyandargs.find_first_of(" "));
	string args = keyandargs.substr(keyandargs.find_first_of(" ") + 1);
	char* val = "";

	AbstractPlugClass* wrapper = this->wrapperContainer[key];
	if (!strcmp(Msgindex,"not")) {
		wrapper->ProcessMsgUnitAsHexOrStr(msg_in, args.c_str(), &val);
	}
	else {
		int index = atoi(Msgindex);
		UWORD_i16* puremsg = nullptr;
		this->basep->GetPureMsgBody(msg_in, &puremsg);

		wrapper->ProcessMsgUnitAsHexOrStr(puremsg+index, args.c_str(), &val);

	}
	int valpre = strtol(valCertain, NULL, 16);
	int valafter = strtol(val, NULL, 16);
	if (valpre == valafter) {
		return true;
	}
	
	return false;
}


int ParseUnit::ProcPureMsgSection(TiXmlElement * pureMsgRuleCollect, UWORD_i16 * const puremsg_in) {
	UWORD_i16 * puremsg = nullptr;
	TiXmlElement* oneParseRule = pureMsgRuleCollect->FirstChildElement();

	while (oneParseRule != NULL) {
		const char* tag_name = oneParseRule->Value();
		const char* v_index = oneParseRule->Attribute("index");
		const char* v_name = oneParseRule->Attribute("name");

		int v_i = atoi(v_index);
		if (!strcmp(v_name, "default")) {
			v_name = tag_name;
		}
		
		string keyandargs = this->cmdEnterpointContainer[tag_name];
		string key = keyandargs.substr(0, keyandargs.find_first_of(" "));
		string args = keyandargs.substr(keyandargs.find_first_of(" ") + 1);
		char* val = "";

		AbstractPlugClass* wrapper = this->wrapperContainer[key];
		wrapper->ProcessMsgUnitAsHexOrStr(puremsg_in + v_i, args.c_str(), &val);

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

	this->basep->EnumKeyWordsInner(&keywords, &num);

	char* value = nullptr;
	for (int i = 0; i < num; i++) {
		this->basep->ProcessMsgUnitAsHexOrStr(msg_in, *(keywords + i), &value);
		
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

	while (this->GetMsgFromCache(&msg_out) != -1) {
		this->MsgBasicParse(msg_out);
		this->fitTimes = 0;//重置统计标志量
		this->FindRuleAdaptAndTranslate(this->patternCollect, this->parseRuleCollect, msg_out);
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
					this->basep->GetPureMsgBody(msg_in, &puremsg);
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


// 收集插件
int ParseUnit::CollectPlugIn(const char* const PlugName, AbstractPlugClass* Plug_In)
{
	string key = PlugName;

	this->wrapperContainer.insert(make_pair(PlugName, Plug_In));
	return 0;
}
