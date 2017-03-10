#include "ExtensionLoader.h"


ExtensionLoader::ExtensionLoader()
{
}


ExtensionLoader::~ExtensionLoader()
{
}


// ����һ����������֧�ְ���ÿ��Ӧ�ó���ʵ��������Ҫһ��������
int ExtensionLoader::LoadNewParseBaseExtension(const char* const libraryName, char**  argv, int argc, StandardBaseSupportInterface** ExtensionRefOut)
{
	USES_CONVERSION;
	//���صײ�֧�ְ��������
	typedef StandardBaseSupportInterface* (*LoadParseBaseUnit)(char** argv, int argc);


	//����һ���ײ����֧�ְ�
	HMODULE hdll = LoadLibrary(A2W(libraryName));
	if (hdll == NULL) { 
		return 1;
	}

	// ��ȡ��ȡ��������
	LoadParseBaseUnit LoadBase = (LoadParseBaseUnit)GetProcAddress(hdll, "GetNewParseBaseInstancePtr");
	if (LoadBase == NULL) {
		FreeLibrary(hdll);
		return 2;
	}

	// ��ȡһ����׼���
	*ExtensionRefOut = LoadBase(argv, argc);

	return 0;
}


// ���ر�׼��ǿ�������ʹ��
int ExtensionLoader::LoadNewParseEnhanceExtension(const char* const libraryName, char**  argv, int argc, StandardExtensionInterface** ExtensionRefOut)
{
	USES_CONVERSION;
	//������չ����֧�ֲ������
	typedef StandardExtensionInterface* (*LoadParseExtensionUnit)(char** const argv, int argc);


	//����һ������������Ϣ����չ��
	HMODULE hdll_e = LoadLibrary(A2W(libraryName));
	if (hdll_e == NULL) {
		return 1;
	}

	// ��ȡ��ȡ��������
	LoadParseExtensionUnit LoadExtension = (LoadParseExtensionUnit)GetProcAddress(hdll_e, "GetNewParseExtensionInstancePtr");
	if (LoadExtension == NULL) {
		FreeLibrary(hdll_e);
		return 2;
	}

	*ExtensionRefOut = LoadExtension(argv, argc);

	return 0;
}

