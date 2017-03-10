#pragma once

#include "AbstractPlugClass.h"
#include "Macro_Global.h"

class CmdWrapper
{
public:
	CmdWrapper();
	virtual ~CmdWrapper();
private:
	char* DLL_lib_key;
	char* Args;
	AbstractPlugClass* WrapperAimed;
public:
	virtual int ProcessMsgUnitAsHexOrStr(char** bufferOut);
	virtual int LoadCmdAndArgs(const char* const CmdRel, AbstractPlugClass * WrapperAimed);
};

