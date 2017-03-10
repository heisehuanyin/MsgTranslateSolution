#include "ExtensionLoader.h"


ExtensionLoader::ExtensionLoader()
{
}


ExtensionLoader::~ExtensionLoader()
{
}


// 加载一个基础解析支持包，每个应用程序实例至少需要一个基础包
int ExtensionLoader::LoadNewParseBaseExtension(const char* const libraryName, char**  argv, int argc, StandardBaseSupportInterface** ExtensionRefOut)
{
	USES_CONVERSION;
	//加载底层支持包插件函数
	typedef StandardBaseSupportInterface* (*LoadParseBaseUnit)(char** argv, int argc);


	//加载一个底层解析支持包
	HMODULE hdll = LoadLibrary(A2W(libraryName));
	if (hdll == NULL) { 
		return 1;
	}

	// 获取提取插件的入口
	LoadParseBaseUnit LoadBase = (LoadParseBaseUnit)GetProcAddress(hdll, "GetNewParseBaseInstancePtr");
	if (LoadBase == NULL) {
		FreeLibrary(hdll);
		return 2;
	}

	// 提取一个基准插件
	*ExtensionRefOut = LoadBase(argv, argc);

	return 0;
}


// 加载标准增强解析插件使用
int ExtensionLoader::LoadNewParseEnhanceExtension(const char* const libraryName, char**  argv, int argc, StandardExtensionInterface** ExtensionRefOut)
{
	USES_CONVERSION;
	//加载拓展解析支持插件函数
	typedef StandardExtensionInterface* (*LoadParseExtensionUnit)(char** const argv, int argc);


	//加载一个处理总线消息的拓展包
	HMODULE hdll_e = LoadLibrary(A2W(libraryName));
	if (hdll_e == NULL) {
		return 1;
	}

	// 获取提取插件的入口
	LoadParseExtensionUnit LoadExtension = (LoadParseExtensionUnit)GetProcAddress(hdll_e, "GetNewParseExtensionInstancePtr");
	if (LoadExtension == NULL) {
		FreeLibrary(hdll_e);
		return 2;
	}

	*ExtensionRefOut = LoadExtension(argv, argc);

	return 0;
}

