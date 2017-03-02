// MsgHeadParse.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "MsgHeadParse.h"
#include <stdio.h>


StandardExtensionInterface* GetNewParseExtensionInstancePtr(char** argv, int argc) {
	return new MsgHead_Parse();
}

MsgHead_Parse::MsgHead_Parse()
{
	this->argsItem[0] = "DIRECT_HEX";
}


MsgHead_Parse::~MsgHead_Parse()
{
}


int MsgHead_Parse::EnumKeyWordsInner(char*** argsArrayOut, int* argsCount)
{
	*argsArrayOut = this->argsItem;
	*argsCount = 1;
	return 0;
}


int MsgHead_Parse::ProcessMsgUnit(const UWORD_i16* const ptr_value_first, const char* const args, char** bufferOut)
{
	sprintf_s(*bufferOut, 20, "%x", *ptr_value_first);
	return 0;
}
