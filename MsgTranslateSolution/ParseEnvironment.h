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
	virtual int GetOneMsg(UWORD_i16** original_msg);

	//�˶����е�����Э�飬����һ����Ϣ
	virtual int FindRuleAdaptAndTranslate(TiXmlElement* supperPattern, TiXmlElement* supperParseRule, UWORD_i16 * const msg_in);

	

	//�������������Ϣ
	virtual int ProcPureMsgSection(TiXmlElement * pureMsgRuleCollect, UWORD_i16 * const msg_in);//��������������Ϣ


	//������ؽ����ײ��������ֵ
	virtual int MsgBasicParse(const UWORD_i16* const msg_in);



	const char* binaryFilePath;//����
	const char* StrictStr;//�����ĿԼ���ַ���
	FILE* outputFilePtr;
	UWORD_i16* OriginalMsgCache;//�ֶ�д��Ļ����



	//�˶��Ƿ�������߽�������
	virtual bool CheckCriterion(const char* const tagName, const char* const Msgindex, const char* const valCertain, UWORD_i16 * const msg_in);



	ParseEnviroments* prsEnv;
	int fitTimes;
};

