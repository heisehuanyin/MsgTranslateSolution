#pragma once
#include "Macro_Global.h"
#include "PlugWrapper.h"
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
	virtual int GetMsgFromCache(UWORD_i16** original_msg);

	//核对所有的总线协议，解析一条消息
	virtual int FindRuleAdaptAndTranslate(TiXmlElement* supperPattern, TiXmlElement* supperParseRule, const UWORD_i16 * const msg_in);

	//收集加载过程中获得的插件
	virtual int CollectPlugIn(const char* const PlugName, StandardExtensionInterface* WrapperIn);
	virtual int CollectPlugIn(const char* const PlugName, StandardParseBaseSupportInterface* WrapperIn);
	
	//加载文件中引用的解析库
	virtual int LoadParseLibrary();
	
	//加载定义的命令入口
	virtual int LoadCmdEnterPoint();

	//加载匹配模式
	virtual int LoadPatternAndParseRule();

	//提取已经收集的wrappper
	virtual PlugWrapper* GetPlugWrapper(const char * const PlugName);

	//手机命令引用点
	virtual int CollectCmdEnterPoint(const char* const CmdName, const char* const libraryKeyAndArgs);

	//处理纯粹的总线消息
	virtual int ProcPureMsgSection(TiXmlElement * pureMsgRuleCollect, const UWORD_i16 * const msg_in);//解析纯粹总线消息


	//翻译相关解析底层包基础键值
	virtual int MsgBasicParse(const UWORD_i16* const msg_in);



	StandardParseBaseSupportInterface* basep;
	std::map<std::string, PlugWrapper*> wrapperContainer;//wrapper容器
	std::map<std::string, std::string> cmdEnterpointContainer;
	ExtensionLoader* loadTools;//加载器
	TiXmlDocument* doc;
	TiXmlElement* patternCollect;// 存储经常使用的pattern集合节点
	TiXmlElement* parseRuleCollect;// 存储常用的解析规则集合节点
	const char* binaryFilePath;//二进制文件路径，数据源
	const char* StrictStr;//输出条目约束字符串
	FILE* outputFilePtr;
	UWORD_i16* OriginalMsgCache;//手动写入的缓冲地
	UWORD_i16* PureMsg;
	const char* parseBaseDocPath;


	////////////////////////////////////////////---------------------------------------------------
	virtual int SetPureMsg(const UWORD_i16* const PureMsg);

	


	//核对是否符合总线解析规则
	virtual bool CheckCriterion(const char* const tagName, const char* const Msgindex, const char* const valCertain, const UWORD_i16* const msg_in);



	ParseEnviroments* prsEnv;
};

