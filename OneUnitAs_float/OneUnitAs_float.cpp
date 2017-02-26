#define STDINTERFACE_EXPORTS 1

// OneUnitAs_float.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "OneUnitAs_float.h"
#include "../MsgTranslateSolution/Macro_Global.h"
#include <stdio.h>



OneWordAs_float::OneWordAs_float()
{
	this->argsItem[0] = "NO_Proc";
	this->argsItem[1] = "MULTIPLY_10";
	this->argsItem[2] = "DIVIDE_10";
	this->argsItem[3] = "MULTIPLY_100";
	this->argsItem[4] = "DIVIDE_100";
	this->argsItem[5] = "MULTIPLY_1000";
	this->argsItem[6] = "DIVIDE_1000";
	this->argsItem[7] = "MULTIPLY_10000";
	this->argsItem[8] = "DIVIDE_10000";
}


OneWordAs_float::~OneWordAs_float()
{
}


int OneWordAs_float::EnumKeyWordsInner(char*** argsArrayOut, int* argsCount)
{
	*argsArrayOut = this->argsItem;
	*argsCount = 9;
	return 0;
}


int OneWordAs_float::ProcessMsgUnit(const UWORD_i16* const ptr_value_first, const char* const args, char** bufferOut)
{
	float fvalue = *ptr_value_first;
	char temp[2048] = "";

	for (int i = 0; i < 9; i++)
	{
		if (!strcmp(args, this->argsItem[i]))
		{
			for (int mm = 1; mm <= i ; mm++)
			{
				if (i%2==1 && mm%2==1)
				{
					fvalue *= 10;
				}
				else if (mm%2==0)
				{
					fvalue /= 10;
				}

			}

			sprintf_s(temp, 20, "%f", fvalue);
			*bufferOut = temp;

			return 0;
		}
	}

	return 1;
}

StandardExtensionInterface* GetNewParseExtensionInstancePtr(char** argv, int argc) {
	return new OneWordAs_float();
}