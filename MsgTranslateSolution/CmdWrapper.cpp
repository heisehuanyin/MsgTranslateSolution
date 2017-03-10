#include "CmdWrapper.h"



CmdWrapper::CmdWrapper()
	: DLL_lib_key(NULL)
	, Args(NULL)
	, WrapperAimed(NULL)
{
}


CmdWrapper::~CmdWrapper()
{
}


int CmdWrapper::ProcessMsgUnitAsHexOrStr(char** bufferOut)
{
	
	return 0;
}


int CmdWrapper::LoadCmdAndArgs(const char* const CmdRel, AbstractPlugClass * WrapperAimed)
{
	return 0;
}
