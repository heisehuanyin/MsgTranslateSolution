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
#include "AbstractPlugClass.h"

class StandardParseBaseSupportInterface :public AbstractPlugClass
{
public:
	~StandardParseBaseSupportInterface() {};

	// ���ݴ���Ķ�ά�ַ��������ȡ������Ϣ�е���Ϣ��ͨ��bufferOut������Ϣ�����뵽���������жϹ���
	// ���������msgArray,�������������ȡ��ԭʼ������Ϣ��
	// ���������argv��������ַ�������,�洢����Ĳ�����
	// ���������bufferOut,�����õ�������ͨ���˻����������������Ҫ���н���ַ���ָ�룬
	//			������֮����Ҫ���ڱ���ָ��ֵ������ֱ���ͷŵ�
	virtual int GetKeyWords(const UWORD_i16* const msgArray , const char* const argv, char** bufferOut) = 0;

	// ��ȡ������������ģ�����ṩ��������Ϣ������ʽ
	// ���������argsArrayOut,��ȡ��ģ���ṩ�Ľ�����������з�ʽ�������Ҫ���н���ַ���ָ�룬
	//			������֮����Ҫ���ڱ���ָ��ֵ������ֱ���ͷŵ�
	// ���������argsCount����ʽ����
	virtual int EnumKeyWordsInner(char*** argsArrayOut, int* argsCount) = 0;

	// ������Ϣ���ݴ�ԭʼ��Ϣ����ȡ�����������Ҫ���н���ַ���ָ�룬
	//			������֮����Ҫ���ڱ���ָ��ֵ������ֱ���ͷŵ�
	virtual int GetPureMsgBody(const UWORD_i16* const msgBufin, UWORD_i16 ** bufferOut) = 0;

	virtual int GetPlugTypeMsg(char ** bufferOut) {
		*bufferOut = "BaseSupport";
		return 0;
	}
	virtual int OpenBinaryDataFile(const char* const filePath) = 0;

	//����ֵ��ʶ�Ƿ���ֵ���ǵĻ�����0�����򷵻�-1,���ڱ�־�Ƿ����
	//�����Ҫ���н����Ϣָ�룬������֮����Ҫ���ڱ���ָ��ֵ������ֱ���ͷŵ�
	virtual int GetOneOriginalMsg(UWORD_i16** bufferOut) = 0;
};


//��������ָ�룬��Ҫÿ��dll����ʵ�ִ˺�������������ͨ���˺�������
extern "C" STDINTERFACE_API StandardParseBaseSupportInterface* GetNewParseBaseInstancePtr(char** argv, int argc = 0);