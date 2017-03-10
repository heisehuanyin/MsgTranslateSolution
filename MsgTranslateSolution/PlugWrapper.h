#pragma once
#include "Macro_Global.h"
#include "StandardExtensionInterface.h"
#include "StandardParseBaseSupportInterface.h"

class PlugWrapper
{
public:
	PlugWrapper();
	virtual ~PlugWrapper();
	virtual int ProcessMsgUnitAsHexOrStr(const UWORD_i16* const MsgArray, const char* const args, char** bufferOut);
private:
	bool IsBaseSupport;
	StandardExtensionInterface* enhancePlug;
	StandardParseBaseSupportInterface* baseSupport;
public:
	virtual int CollectPlugInstance(StandardExtensionInterface* PlugIn);
	virtual int CollectPlugInstance(StandardParseBaseSupportInterface* PlugIn);
};

