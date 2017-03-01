#pragma once

#include "StandardParseBaseSupportInterface.h"
#include "StandardExtensionInterface.h"
#include <Windows.h>
#include <atlbase.h>

class ExtensionLoader
{
public:
	ExtensionLoader();
	virtual ~ExtensionLoader();
	// ����һ����������֧�ְ���ÿ��Ӧ�ó���ʵ��������Ҫһ��������
	virtual int LoadNewParseBaseExtension(const char* const libraryName, char**  argv, int argc, StandardParseBaseSupportInterface** ExtensionRefOut);
	// ���ر�׼��ǿ�������ʹ��
	virtual int LoadNewParseEnhanceExtension(const char* const libraryName, char**  argv, int argc, StandardExtensionInterface** ExtensionRefOut);
};

