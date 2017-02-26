// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�  
// ��ı�׼�������� DLL �е������ļ��������������϶���� STDINTERFACE_EXPORTS  
// ���ű���ġ���ʹ�ô� DLL ��  
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ  
// STDINTERFACE_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���  
// ������Ϊ�Ǳ������ġ�  


#ifdef STDINTERFACE_EXPORTS  
#define STDINTERFACE_API __declspec(dllexport)  
#else  
#define STDINTERFACE_API __declspec(dllimport)  
#endif  

#pragma once
#include "../MsgTranslateSolution/Macro_Global.h"

class StandardParseBaseSupportInterface
{
public:
	~StandardParseBaseSupportInterface() {};

	// ���ݴ���Ķ�ά�ַ��������ȡ������Ϣ�е���Ϣ��ͨ��bufferOut������Ϣ�����뵽���������жϹ���
	// ���������msgArray,�������������ȡ��ԭʼ������Ϣ��
	// ���������argv��������ַ�������,�洢����Ĳ�����
	// ���������bufferOut,�����õ�������ͨ���˻�����������
	virtual int GetKeyWords(const UWORD_i16* const msgArray , const char* const argv, char** bufferOut) = 0;

	// ��ȡ������������ģ�����ṩ��������Ϣ������ʽ
	// ���������argsArrayOut,��ȡ��ģ���ṩ�Ľ�����������з�ʽ
	// ���������argsCount����ʽ����
	virtual int EnumKeyWordsInner(char*** argsArrayOut, int* argsCount) = 0;

	// ������Ϣ���ݴ�ԭʼ��Ϣ����ȡ����
	virtual int GetPureMsgBody(const UWORD_i16* const msgBufin,UWORD_i16* bufferOut) = 0;
};


//��������ָ�룬��Ҫÿ��dll����ʵ�ִ˺�������������ͨ���˺�������
extern "C" STDINTERFACE_API StandardParseBaseSupportInterface* GetNewParseBaseInstancePtr(char** argv, int argc = 0);