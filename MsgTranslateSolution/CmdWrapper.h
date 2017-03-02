#pragma once
#include "PlugWrapper.h"

class CmdWrapper
{
public:
	CmdWrapper();
	virtual ~CmdWrapper();
private:
	char* DLL_lib_key;
	char* Args;
	PlugWrapper* WrapperAimed;
public:
	virtual int GetKeyValueFromMsg(char** bufferOut);
	virtual int LoadCmdAndArgs(const char* const CmdRel, PlugWrapper* WrapperAimed);
};

