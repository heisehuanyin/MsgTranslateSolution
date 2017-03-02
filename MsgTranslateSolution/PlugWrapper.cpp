#include "PlugWrapper.h"


PlugWrapper::PlugWrapper()
	: IsBaseSupport(false)
	, enhancePlug(NULL)
	, baseSupport(NULL)
{
}


PlugWrapper::~PlugWrapper()
{
}


int PlugWrapper::GetKeyValueFromMsg(const UWORD_i16* const MsgArray, const char* const args, char** bufferOut)
{
	if (this->IsBaseSupport)
	{
		this->baseSupport->GetKeyWords(MsgArray, args, bufferOut);
	}
	else
	{
		this->enhancePlug->ProcessMsgUnit(MsgArray, args, bufferOut);
	}
	return 0;
}


int PlugWrapper::CollectPlugInstance(StandardExtensionInterface* PlugIn)
{
	this->enhancePlug = PlugIn;
	this->IsBaseSupport = false;
	return 0;
}


int PlugWrapper::CollectPlugInstance(StandardParseBaseSupportInterface* PlugIn)
{
	this->baseSupport = PlugIn;
	this->IsBaseSupport = true;
	return 0;
}
