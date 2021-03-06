#pragma once
#include "Macro_Global.h"
#include <string>
#include <map>
#include "tinystr.h"
#include "tinyxml.h"
#include "ExtensionLoader.h"
#include <vector>
#include "ParseEnviroments.h"

class ParseUnit {
public:
	ParseUnit();
	virtual ~ParseUnit();

	//初始化整个解析环境
	//传入参数：parseBase，解析依据的xml文件名称
	//传入参数：binaryDataFile，解析所用到的数据源，为NULL的时候逐条写入，否则指定数据文件
	//传入参数：strictString，指定输出那些条目，初始化为NULL输出全部条目
	//传入参数：outputFile，指定输出目标，为NULL的时候打印到屏幕，否则为指定文件
	virtual int initSelf(const char* const parseBase,const char* const binaryDataFile, const char* const strictString, const char* const outputFile);

	//单独解析一条消息的时候(典型场景实时解析)
	//必须首先设置一条消息，之后再调用解析函数
	virtual int SetOriginalMsg(UWORD_i16 * const OriginalMsg);

	//执行解析动作
	virtual int translateMsgAtNow();


private:
	//从缓冲或者是底层插件中获取一条总线消息
	//返回值：0，正常获取了总线消息
	//返回值：-1，总线消息已经结束了，这次没有获取到消息
	virtual int GetOneMsg(UWORD_i16** original_msg);

	//核对所有的总线协议，解析一条消息
	virtual int FindRuleAdaptAndTranslate(TiXmlElement* supperPattern, TiXmlElement* supperParseRule, UWORD_i16 * const msg_in);

	

	//处理纯粹的总线消息
	virtual int ProcPureMsgSection(TiXmlElement * pureMsgRuleCollect, UWORD_i16 * const msg_in);//解析纯粹总线消息


	//翻译相关解析底层包基础键值
	virtual int MsgBasicParse(const UWORD_i16* const msg_in);



	const char* binaryFilePath;//二进
	const char* StrictStr;//输出条目约束字符串
	FILE* outputFilePtr;
	UWORD_i16* OriginalMsgCache;//手动写入的缓冲地



	//核对是否符合总线解析规则
	virtual bool CheckCriterion(const char* const tagName, const char* const Msgindex, const char* const valCertain, UWORD_i16 * const msg_in);



	ParseEnviroments* prsEnv;
	int fitTimes;
};

