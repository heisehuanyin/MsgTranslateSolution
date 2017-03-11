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
	char* t1 = "一个风骚的利用实体字符串初始化的常亮缓冲区，对，就是常亮而不是常量！";
	char* t2 = "一个风骚的利用实体字符串初始化的没什么用的缓冲区，一般情况下也不存储东西！";

	sprintf_s(this->linkRel, 1024, "%s", strtok_s(linkRelAndArguments, " ", &t1));
	sprintf_s(this->arguments, 1024, "%s", strtok_s(t1, " ", &t2));

	return 0;
}
