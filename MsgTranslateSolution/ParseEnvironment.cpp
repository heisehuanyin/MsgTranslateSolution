#include "ParseEnvironment.h"

ParseEnvironment::~ParseEnvironment()
{
}


ParseEnvironment::ParseEnvironment(const char* const filePath, const char* const StrictStr)
	: filePath(NULL)
	, StrictStr(NULL)
{
}


int ParseEnvironment::initSelf()
{
	return 0;
}
