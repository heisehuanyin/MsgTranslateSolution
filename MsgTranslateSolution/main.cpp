/**������2017��02��23��
***����Ԫ������Ҫ���ڸ��ٷ���1553B������Ϣ
***�������1553B����Э���ļ�����������
***/

#include <iostream>
#include "StandardParseBaseSupportInterface.h"
#include "StandardExtensionInterface.h"
#include <Windows.h>
#include "ExtensionLoader.h"
#include "tinystr.h"
#include "tinyxml.h"
#include "ParseEnvironment.h"
#include <string.h>



//���ڷ��빤���������
//���������argc�������ĸ���
//���������argv������
//��ʽ������ MsgTranslateSolution  /base xxxx.xml   /source xxxx.dat     /group dm_group
//���������� ��������					ָ�������׼		ָ����Ϣ��¼�ļ�		ָ���������
//��ʽ������ MsgTranslateSolution  /help
//���������� ��������					��Ҫ�����а���
//��ʽ������ MsgTranslateSolution  /expose
//���������� ��������					ָ����Ϊ�����������ڲ����Ʋ���5
void main(int argc, char** argv) {
	//����ѡ���ӡ��������
	if (strcmp(*(argv + 1), "/help") == 0) {
		printf("������ע�ͣ���ɳ�����ٿ������");
		return;
	}

	//����ѡ��2����ӡ���������ѡ��
	if (strcmp(*(argv + 1), "/expose") == 0) {
		WIN32_FIND_DATAW ffd;

		HANDLE hFind = FindFirstFile(L".\\*.dll", &ffd);

		do {
			if (!(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				wprintf(L"%s\n\n", ffd.cFileName);
				char ttmm[MAX_PATH] = "";


				WideCharToMultiByte(CP_ACP, 0, ffd.cFileName, wcslen(ffd.cFileName), ttmm, MAX_PATH, 0, 0);

				ExtensionLoader loadTools = ExtensionLoader();

				AbstractPlugClass* basep = NULL;
				int rtn = loadTools.LoadNewParseBaseExtension(ttmm, nullptr, 0, (StandardParseBaseSupportInterface**)&basep);

				if (rtn == 2) {
					rtn = loadTools.LoadNewParseEnhanceExtension(ttmm, nullptr, 0, (StandardExtensionInterface**)&basep);
				}

				char* ttmp = "";
				char ** ab = nullptr;
				int ntemp = 0;
				basep->GetPlugTypeMsg(&ttmp);
				printf("������ͣ�%s\n", ttmp);

				if (!strcmp(ttmp, "BaseSupport")) {
					((StandardParseBaseSupportInterface*)basep)->EnumKeyWordsInner(&ab, &ntemp);
					printf("�ڲ�����:\n");
					for (int i = 0; i < ntemp; i++) {
						printf("  %d->\t%s %s\n", i, ttmm, *(ab + i));
					}
				}
				else {
					((StandardExtensionInterface*)basep)->EnumKeyWordsInner(&ab, &ntemp);
					printf("�ڲ�����:\n");
					for (int i = 0; i < ntemp; i++) {
						printf("  %d->\t%s %s\n", i, ttmm, *(ab + i));
					}
				}
				printf("\n\n\n");
			}

		} while (FindNextFile(hFind, &ffd));

		FindClose(hFind); // �رղ��Ҿ��

		return;
	}

	//������������ʼ����
	if (strcmp(*(argv + 1), "/base") == 0 && strcmp(*(argv + 3), "/source") == 0) {

		//���û����������ر�����ʵ�ִ�������
		ParseUnit* parseUnit = new ParseUnit();


		parseUnit->initSelf(*(argv + 2), *(argv + 4), NULL, NULL);
		parseUnit->translateMsgAtNow();
	}

	return;
}


