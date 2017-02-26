#pragma once

#include "StandardParseBaseSupportInterface.h"
#include "StandardExtensionInterface.h"
#include "StandardMsgSourceInterface.h"
#include <Windows.h>
#include <atlbase.h>

class ExtensionLoader
{
public:
	ExtensionLoader();
	virtual ~ExtensionLoader();
	// 加载一个基础解析支持包，每个应用程序实例至少需要一个基础包
	virtual int LoadNewParseBaseExtension(const char* const libraryName, char**  argv, int argc, StandardParseBaseSupportInterface** ExtensionRefOut);
	// 加载标准增强解析插件使用
	virtual int LoadNewParseEnhanceExtension(const char* const libraryName, char**  argv, int argc, StandardExtensionInterface** ExtensionRefOut);
	// 加载消息源插件
	virtual int LoadNewMsgSourceExtension(const char* const libraryName, char**  argv, int argc, StandardMsgSourceInterface** ExtensionRefOut);
};

