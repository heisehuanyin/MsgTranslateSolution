#pragma once

#include "../MsgTranslateSolution/StandardExtensionInterface.h"
#include "../MsgTranslateSolution/Macro_Global.h"



class CodeMarkProcess:public StandardExtensionInterface
{
public:
	CodeMarkProcess();
	virtual ~CodeMarkProcess();
	virtual int EnumKeyWordsInner(char*** argsArrayOut, int* argsCount);
	virtual int ProcessMsgUnitAsHexOrStr(const UWORD_i16* const ptr_value_first,const char* const args, char** bufferOut);
private:
	char* argsItem[20];
	char content[200];
};
