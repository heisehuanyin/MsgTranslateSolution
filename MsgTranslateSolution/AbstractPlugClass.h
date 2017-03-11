#pragma once
#include "Macro_Global.h"

class AbstractPlugClass
{
public:
	virtual int GetPlugTypeMsg(char** BufferOut)=0;


	// ���ݴ���Ķ�ά�ַ��������ȡ������Ϣ�е���Ϣ��ͨ��bufferOut������Ϣ�����뵽���������жϹ���
	// ���������ptr_value_first,�������������ȡ��ԭʼ������Ϣ��
	// ���������argv��������ַ�������,�洢����Ĳ�����
	// ���������bufferOut,�����õ�������ͨ���˻����������������Ҫ���н���ַ���ָ�룬
	//			������֮����Ҫ���ڱ���ָ��ֵ������ֱ���ͷŵ�
	virtual int ProcessMsgUnitAsHexOrStr(const UWORD_i16* const ptr_value_first, const char* const argv, char** bufferOut) = 0;

};

