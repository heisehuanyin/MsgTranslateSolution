#include "stdafx.h"
#include "targetver.h"
#include "Code_mark_parse.h"
#include "../MsgTranslateSolution/Macro_Global.h"
#include "../MsgTranslateSolution/StandardExtensionInterface.h"
#include <stdio.h>

#define STDINTERFACE_EXPORTS


CodeMarkProcess::CodeMarkProcess()
{
	this->argsItem[0] = "WORD_1";
	this->argsItem[1] = "WORD_2";
	this->argsItem[2] = "WORD_3";
	this->argsItem[3] = "WORD_4";
	this->argsItem[4] = "WORD_5";
	this->argsItem[5] = "WORD_6";
	this->argsItem[6] = "WORD_7";
	this->argsItem[7] = "WORD_8";
}


CodeMarkProcess::~CodeMarkProcess()
{
}


int CodeMarkProcess::EnumKeyWordsInner(char*** argsArrayOut, int* argsCount)
{
	*argsArrayOut = this->argsItem;
	*argsCount = 8;
	return 0;
}


int CodeMarkProcess::ProcessMsgUnit(const UWORD_i16* const ptr_value_first, const char* const args, char** bufferOut)
{
	char temp[2048] = "";

	for (int i = 0; i < 8; i++)
	{
		if (!strcmp(args,this->argsItem[i]))
		{
			for (int is = 0; is < i+1; is++)
			{
				sprintf_s(temp, 20, "%x", *(ptr_value_first + is));
			}

			return 0;
		}
	}
	return 1;
}


StandardExtensionInterface* GetNewParseExtensionInstancePtr(char** argv, int argc) {
	return new CodeMarkProcess();
}