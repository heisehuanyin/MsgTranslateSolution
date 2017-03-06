#include "ParseEnvironment.h"





using namespace std;

ParseUnit::~ParseUnit() {}


ParseUnit::ParseUnit()
	: binaryFilePath(NULL)
	, StrictStr(NULL)
	, PureMsg(NULL), doc(NULL)
	, parseBaseDocPath(NULL)
	, loadTools(NULL)
	, basep(NULL)
	, outputFilePtr(NULL)
	, OriginalMsgCache(NULL)
	, patternCollect(NULL)
	, parseRuleCollect(NULL), prsEnv(NULL) {}


int ParseUnit::initSelf(const char* const parseBase, const char* const binaryDataFile, const char* const strictString, const char* const outputFile) {
	this->parseBaseDocPath = parseBase;
	this->binaryFilePath = binaryDataFile;
	this->StrictStr = strictString;

	this->doc = new TiXmlDocument(parseBaseDocPath);
	this->doc->LoadFile();

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



int ParseUnit::SetPureMsg(const UWORD_i16* const PureMsg) {
	return 0;
}


int ParseUnit::CollectPlugIn(const char* const PlugName, StandardExtensionInterface* WrapperIn) {
	PlugWrapper* wrapper = new PlugWrapper();
	wrapper->CollectPlugInstance(WrapperIn);

	string key = PlugName;

	this->wrapperContainer.insert(make_pair(PlugName, wrapper));

	return 0;
}


int ParseUnit::CollectPlugIn(const char* const PlugName, StandardParseBaseSupportInterface* WrapperIn) {
	PlugWrapper* wrapper = new PlugWrapper();
	wrapper->CollectPlugInstance(WrapperIn);

	string key = PlugName;

	this->wrapperContainer.insert(make_pair(PlugName, wrapper));

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


PlugWrapper* ParseUnit::GetPlugWrapper(const char * const PlugName) {
	string key = PlugName;
	map<string, PlugWrapper*>::iterator it = this->wrapperContainer.end();

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
	
	string keyandargs = this->cmdEnterpointContainer[tagName];
	string key = keyandargs.substr(0, keyandargs.find_first_of(" "));
	string args = keyandargs.substr(keyandargs.find_first_of(" ") + 1);
	char* val = "";

	PlugWrapper* wrapper = this->wrapperContainer[key];
	if (!strcmp(Msgindex,"not")) {
		wrapper->GetKeyValueFromMsg(msg_in, args.c_str(), &val);
	}
	else {
		int index = atoi(Msgindex);
		UWORD_i16* puremsg = nullptr;
		this->basep->GetPureMsgBody(msg_in, &puremsg);

		wrapper->GetKeyValueFromMsg(puremsg+index, args.c_str(), &val);

	}

	int valpre = atoi(valCertain);
	int valafter = atoi(val);
	if (valpre == valafter) {
		return true;
	}
	
	return false;
}


int ParseUnit::ProcPureMsgSection(TiXmlElement * pureMsgRuleCollect, UWORD_i16 * const msg_in) {
	UWORD_i16 * puremsg = nullptr;
	
	this->basep->GetPureMsgBody(msg_in, &puremsg);

	return 0;
}


int ParseUnit::MsgBasicParse(const UWORD_i16* const msg_in) {
	char** keywords = nullptr;
	int num = 0;

	this->basep->EnumKeyWordsInner(&keywords, &num);

	char* value = nullptr;
	for (int i = 0; i < num; i++) {
		this->basep->GetKeyWords(msg_in, *(keywords + i), &value);

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
		this->FindRuleAdaptAndTranslate(this->patternCollect, this->parseRuleCollect, msg_out);
	}
	return 0;
}


int ParseUnit::FindRuleAdaptAndTranslate(TiXmlElement* patternCollect, TiXmlElement* parseRuleCollect, UWORD_i16 * const msg_in) {
	TiXmlElement* elelm = patternCollect->FirstChildElement();
	int fitTimes = 0;

	while (elelm != NULL) {
		const char* tagname = elelm->Value();
		const char* varIndex = elelm->Attribute("index");
		TiXmlElement* oneRuleAdapted = parseRuleCollect->FirstChildElement();

		while (oneRuleAdapted != NULL) {
			const char* target_value = oneRuleAdapted->Attribute("value");

			if (this->CheckCriterion(tagname, varIndex, target_value, msg_in)) {
				if (elelm->NoChildren()) {
					this->ProcPureMsgSection(oneRuleAdapted, msg_in);
					fitTimes += 1;
				}
				else {
					this->FindRuleAdaptAndTranslate(elelm, oneRuleAdapted, msg_in);
				}
			}
			oneRuleAdapted = oneRuleAdapted->NextSiblingElement();
		}
		if (fitTimes != 1) {
			printf("解析失败，未发现适配的解析规则(0)或者多次适配，解析规则存在歧义(>1)，节点：%s,适配次数:%d\n", tagname, fitTimes);
		}
		elelm = elelm->NextSiblingElement();
	}

	return 0;
}
