#pragma once
#include "../MsgTranslateSolution/StandardExtensionInterface.h"
#include "../MsgTranslateSolution/Macro_Global.h"

class TwoWordAs_union :
	public StandardExtensionInterface
{
public:
	TwoWordAs_union();
	virtual ~TwoWordAs_union();
	virtual int EnumKeyWordsInner(char*** argsArrayOut, int* argsCount);
	virtual int ProcessMsgUnit(const UWORD_i16* const ptr_value_first, const char* const args, char** bufferOut);
private:
	char* argsItem[20];
};

