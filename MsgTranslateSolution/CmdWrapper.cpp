#include "CmdWrapper.h"
#include <stdio.h>



CmdWrapper::CmdWrapper()
{
}


CmdWrapper::~CmdWrapper()
{
}



int CmdWrapper::initSelf(char* linkRelAndArguments)
{
	char* t1 = "һ����ɧ������ʵ���ַ�����ʼ���ĳ������������ԣ����ǳ��������ǳ�����";
	char* t2 = "һ����ɧ������ʵ���ַ�����ʼ����ûʲô�õĻ�������һ�������Ҳ���洢������";

	sprintf_s(this->linkRel, 1024, "%s", strtok_s(linkRelAndArguments, " ", &t1));
	sprintf_s(this->arguments, 1024, "%s", strtok_s(t1, " ", &t2));

	return 0;
}
