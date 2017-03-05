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

	//��ʼ��������������
	//���������parseBase���������ݵ�xml�ļ�����
	//���������binaryDataFile���������õ�������Դ��ΪNULL��ʱ������д�룬����ָ�������ļ�
	//���������strictString��ָ�������Щ��Ŀ����ʼ��ΪNULL���ȫ����Ŀ
	//���������outputFile��ָ�����Ŀ�꣬ΪNULL��ʱ���ӡ����Ļ������Ϊָ���ļ�
	virtual int initSelf(const char* const parseBase,const char* const binaryDataFile, const char* const strictString, const char* const outputFile);

	//��������һ����Ϣ��ʱ��(���ͳ���ʵʱ����)
	//������������һ����Ϣ��֮���ٵ��ý�������
	virtual int SetOriginalMsg(UWORD_i16 * const OriginalMsg);

	//ִ�н�������
	virtual int translateMsgAtNow();


private:
	//�ӻ�������ǵײ����л�ȡһ��������Ϣ
	//����ֵ��0��������ȡ��������Ϣ
	//����ֵ��-1��������Ϣ�Ѿ������ˣ����û�л�ȡ����Ϣ
	virtual int GetMsgFromCache(UWORD_i16** original_msg);

	//�˶����е�����Э�飬����һ����Ϣ
	virtual int FindRuleAdaptAndTranslate(TiXmlElement* supperPattern, TiXmlElement* supperParseRule, const UWORD_i16 * const msg_in);

	//�ռ����ع����л�õĲ��
	virtual int CollectPlugIn(const char* const PlugName, StandardExtensionInterface* WrapperIn);
	virtual int CollectPlugIn(const char* const PlugName, StandardParseBaseSupportInterface* WrapperIn);
	
	//�����ļ������õĽ�����
	virtual int LoadParseLibrary();
	
	//���ض�����������
	virtual int LoadCmdEnterPoint();

	//����ƥ��ģʽ
	virtual int LoadPatternAndParseRule();

	//��ȡ�Ѿ��ռ���wrappper
	virtual PlugWrapper* GetPlugWrapper(const char * const PlugName);

	//�ֻ��������õ�
	virtual int CollectCmdEnterPoint(const char* const CmdName, const char* const libraryKeyAndArgs);

	//�������������Ϣ
	virtual int ProcPureMsgSection(TiXmlElement * pureMsgRuleCollect, const UWORD_i16 * const msg_in);//��������������Ϣ


	//������ؽ����ײ��������ֵ
	virtual int MsgBasicParse(const UWORD_i16* const msg_in);



	StandardParseBaseSupportInterface* basep;
	std::map<std::string, PlugWrapper*> wrapperContainer;//wrapper����
	std::map<std::string, std::string> cmdEnterpointContainer;
	ExtensionLoader* loadTools;//������
	TiXmlDocument* doc;
	TiXmlElement* patternCollect;// �洢����ʹ�õ�pattern���Ͻڵ�
	TiXmlElement* parseRuleCollect;// �洢���õĽ������򼯺Ͻڵ�
	const char* binaryFilePath;//�������ļ�·��������Դ
	const char* StrictStr;//�����ĿԼ���ַ���
	FILE* outputFilePtr;
	UWORD_i16* OriginalMsgCache;//�ֶ�д��Ļ����
	UWORD_i16* PureMsg;
	const char* parseBaseDocPath;


	////////////////////////////////////////////---------------------------------------------------
	virtual int SetPureMsg(const UWORD_i16* const PureMsg);

	


	//�˶��Ƿ�������߽�������
	virtual bool CheckCriterion(const char* const tagName, const char* const Msgindex, const char* const valCertain, const UWORD_i16* const msg_in);



	ParseEnviroments* prsEnv;
};

