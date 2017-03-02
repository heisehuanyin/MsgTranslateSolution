#pragma once
#include "Macro_Global.h"
#include "PlugWrapper.h"

class ParseEnvironment
{
public:
	ParseEnvironment(const char* const filePath, const char* const StrictStr);
	virtual ~ParseEnvironment();
private:
	char* filePath;
	char* StrictStr;
public:
	virtual int initSelf();
};

