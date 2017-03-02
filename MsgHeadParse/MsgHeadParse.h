#pragma once
#include "../MsgTranslateSolution/Macro_Global.h"
#include "../MsgTranslateSolution/StandardExtensionInterface.h"

class MsgHead_Parse :
	public StandardExtensionInterface
{
public:
	MsgHead_Parse();
	virtual ~MsgHead_Parse();
private:
	char* argsItem[20];
public:
	virtual int EnumKeyWordsInner(char*** argsArrayOut, int* argsCount);
	virtual int ProcessMsgUnit(const UWORD_i16* const ptr_value_first, const char* const args, char** bufferOut);
};

