#define STDINTERFACE_EXPORTS 1

// TowWordAs_union.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "TowWordAs_union.h"
#include "../MsgTranslateSolution/Macro_Global.h"
#include <stdio.h>

StandardExtensionInterface* GetNewParseExtensionInstancePtr(char** argv, int argc) {
	return new TwoWordAs_union();
}

TwoWordAs_union::TwoWordAs_union()
{
	this->argsItem[0] = "2WORD_AS_float_HBIT_first";
	this->argsItem[1] = "2WORD_AS_float_LBIT_first";
	this->argsItem[2] = "2WORD_AS_int_HBIT_first";
	this->argsItem[3] = "2WORD_AS_int_LBIT_first";
}


TwoWordAs_union::~TwoWordAs_union()
{
}


int TwoWordAs_union::EnumKeyWordsInner(char*** argsArrayOut, int* argsCount)
{
	*argsArrayOut = this->argsItem;

	*argsCount = 4;

	return 0;
}


int TwoWordAs_union::ProcessMsgUnit(const UWORD_i16* const ptr_value_first, const char* const args, char** bufferOut)
{
	char temp[2048] = "";

	for (int i = 0; i < 4; i++)
	{
		if (!strcmp(args,this->argsItem[i]))
		{
			union {
				float fvalue;
				UWORD_i16 mvalue[2];
			} cov_f;

			union {
				int ivalue;
				UWORD_i16 mvalue[2];
			} cov_i;


			switch (i)
			{
				case 0:
					cov_f.mvalue[0] = *ptr_value_first;
					cov_f.mvalue[1] = *(ptr_value_first+1);
					sprintf_s(*bufferOut, 20, "%f", cov_f.fvalue);
					break;
				case 1:
					cov_f.mvalue[1] = *ptr_value_first;
					cov_f.mvalue[0] = *(ptr_value_first + 1);
					sprintf_s(*bufferOut, 20, "%f", cov_f.fvalue);
					break;
				case 2:
					cov_i.mvalue[0] = *ptr_value_first;
					cov_i.mvalue[1] = *(ptr_value_first + 1);
					sprintf_s(*bufferOut, 20, "%d", cov_i.ivalue);
					break;
				case 3:
					cov_i.mvalue[1] = *ptr_value_first;
					cov_i.mvalue[0] = *(ptr_value_first + 1);
					sprintf_s(*bufferOut, 20, "%d", cov_i.ivalue);
					break;
				default:
					break;
			}


			return 0;
		}
	}
	return 1;
}
