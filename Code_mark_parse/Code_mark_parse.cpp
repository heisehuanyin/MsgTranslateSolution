﻿#include "stdafx.h"
#include "targetver.h"
#include "Code_mark_parse.h"
#include "../MsgTranslateSolution/Macro_Global.h"
#include "../MsgTranslateSolution/StandardExtensionInterface.h"
#include <stdio.h>



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


int CodeMarkProcess::ProcessMsgUnitAsHexOrStr(const UWORD_i16* const ptr_value_first, const char* const args, char** bufferOut)
{
	for (int i = 0; i < 200; i++) {
		this->content[i] = NULL;
	}

	for (int i = 0; i < 8; i++)
	{
		if (!strcmp(args,this->argsItem[i]))
		{
			for (int is = 0; is < i+1; is++)
			{
				sprintf_s(this->content, 200, "%s%x", this->content, *(ptr_value_first + is));
			}

			*bufferOut = this->content;

			return 0;
		}
	}
	return 1;
}


StandardExtensionInterface* GetNewParseExtensionInstancePtr(char** argv, int argc) {
	return new CodeMarkProcess();
}