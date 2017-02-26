#ifdef STDINTERFACE_EXPORTS  
#define STDINTERFACE_API __declspec(dllexport)  
#else  
#define STDINTERFACE_API __declspec(dllimport)  
#endif  

#pragma once

#include "../MsgTranslateSolution/Macro_Global.h"


class StandardMsgSourceInterface
{
public:
	~StandardMsgSourceInterface() {};

	// ���ô˺������̴��ƶ��������ļ���������ļ����ڴ�״̬���Ȼ�ر��ļ������һ��״̬����ˢ��
	virtual int OpenOneDataFileAtNow(const char* const DataFilePath) = 0;

	// ��ȡһ��ԭʼ��ʽ��������Ϣ
	virtual int OriginalFormat_PickOneMsg(UWORD_i16** MsgArray_Ptr) = 0;

};



// ���Ӷ�̬���ӿ������������һ���ӿڣ�ÿ����̬dll����Ҫʵ������ӿں�����������ർ�����
extern "C" STDINTERFACE_API StandardMsgSourceInterface* GetNewMsgSourceInstancePtr(char** argv, int argc = 0);
