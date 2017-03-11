#pragma once

#include "AbstractPlugClass.h"
#include "Macro_Global.h"

class CmdWrapper
{
public:
	CmdWrapper();
	virtual ~CmdWrapper();
	char linkRel[1024];
	char arguments[1024];
	virtual int initSelf(char* linkRelAndArguments);
};

