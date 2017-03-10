/**创建于2017年02月23日
***本单元作用主要用于高速翻译1553B总线消息
***翻译基于1553B总线协议文件与总线数据
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



//用于翻译工作的总入口
//输入参数：argc，参数的个数
//输入参数：argv，参数
//格式范例： MsgTranslateSolution  /base xxxx.xml   /source xxxx.dat     /group dm_group
//工作参数： 程序名称					指明翻译基准		指明消息记录文件		指明总线类别
//格式范例： MsgTranslateSolution  /help
//工作参数： 程序名称					需要命令行帮助
//格式范例： MsgTranslateSolution  /expose
//工作参数： 程序名称					指定行为，导出所有内部控制参数5
void main(int argc, char** argv) {
	//帮助选项，打印帮助内容
	if (strcmp(*(argv + 1), "/help") == 0) {
		printf("见程序注释，完成程序后再考虑添加");
		return;
	}

	//帮助选项2，打印插件的所有选项
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



				unsigned short mmmsg[2000] = { 0 };
				for (int ipip = 0; ipip < 2000; ipip++) {
					mmmsg[ipip] = 0xffff;
				}

				char* ttmp = "";
				char* temp = nullptr;
				char ** ab = nullptr;
				int ntemp = 0;
				basep->GetPlugTypeMsg(&ttmp);

				printf("插件类型：%s\n", ttmp);
				printf("提供输入内容：0xfffffffffff…………ffffff\n\n");
				if (!strcmp(ttmp, "BaseSupport")) {
					((StandardParseBaseSupportInterface*)basep)->EnumKeyWordsInner(&ab, &ntemp);
					printf("内部参数与输出范式:\n");
					for (int i = 0; i < ntemp; i++) {
						((StandardParseBaseSupportInterface*)basep)->ProcessMsgUnitAsHexOrStr(mmmsg, *(ab + i), &temp);

						printf("  %d->\t%s %s \t\t\t 输出：%s\n", i, ttmm, *(ab + i),temp);
					}
				}
				else {
					((StandardExtensionInterface*)basep)->EnumKeyWordsInner(&ab, &ntemp);
					printf("内部参数与输出范式:\n");
					for (int i = 0; i < ntemp; i++) {
						((StandardExtensionInterface*)basep)->ProcessMsgUnitAsHexOrStr(mmmsg, *(ab + i), &temp);

						printf("  %d->\t%s %s \t\t\t 输出：%s\n", i, ttmm, *(ab + i), temp);
					}
				}
				printf("\n\n\n");
			}

		} while (FindNextFile(hFind, &ffd));

		FindClose(hFind); // 关闭查找句柄

		return;
	}

	//正常工作，开始解析
	if (strcmp(*(argv + 1), "/base") == 0 && strcmp(*(argv + 3), "/source") == 0) {

		//利用环境类管理相关变量，实现代码整洁
		ParseUnit* parseUnit = new ParseUnit();


		parseUnit->initSelf(*(argv + 2), *(argv + 4), NULL, NULL);
		parseUnit->translateMsgAtNow();
	}

	return;
}


