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



// ������󻯵Ĳ��ʵ�ַ�ʽ������ڴ�ͳ��C�����нṹ��������Ϊ��ȷ���ŵ�
// ÿ��������뱩©�Ļ����ӿ�
class StandardExtensionInterface:public AbstractPlugClass
{
public:
	// ����������������� 
	virtual ~StandardExtensionInterface() {}; 

	// ͨ���˺������õĴ�����Ϣ�������⣬���ݲ����ǵ�һ����������Ϣ�ֵ�һ���ֵ�ָ��,��������Ϊ�������Ϣ���
	virtual int ProcessMsgUnit(const UWORD_i16* const ptr_value_first, const char* const args, char** bufferOut) = 0;

	// �о����п�ѡ����
	virtual int EnumKeyWordsInner(char*** argsArrayOut, int* argsCount) = 0;

	virtual int GetPlugTypeMsg(char ** bufferOut) {
		*bufferOut = "EnhancePlug";
		return 0;
	}

};

// ���Ӷ�̬���ӿ������������һ���ӿڣ�ÿ����̬dll����Ҫʵ������ӿں�����������ർ�����
extern "C" STDINTERFACE_API StandardExtensionInterface* GetNewParseExtensionInstancePtr(char** argv, int argc = 0);

