/**创建于2017年02月23日
***本单元作用主要用于高速翻译1553B总线消息
***翻译基于1553B总线协议文件与总线数据
***/

#include <iostream>
#include "StandardParseBaseSupportInterface.h"
#include "StandardExtensionInterface.h"
#include <Windows.h>
#include "ExtensionLoader.h"




//用于翻译工作的总入口
//输入参数：argc，参数的个数
//输入参数：argv，参数
//格式范例： MsgTranslateSolution  /base xxxx.xml   /source xxxx.dat     /group dm_group
//工作参数： 程序名称			   指明翻译基准		指明消息记录文件	 指明总线类别
//格式范例： MsgTranslateSolution  /help
//求助参数： 程序名称			   需要命令行帮助
void main(int argc, char** argv) {
	//帮助选项，打印帮助内容
	if (strcmp(*(argv + 1), "/help") == 0) {
		printf("格式范例： MsgTranslateSolution  /base xxxx.xml   /source xxxx.dat     /group dm_group\n工作参数： 程序名称		指明翻译基准	指明消息记录文件	指明总线类别\n格式范例： MsgTranslateSolution  /help\n求助参数： 程序名称		需要命令行帮助\n");
		return;
	}

	//帮助选项2，打印插件的所有选项
	// 待完善

	// loadPlug
	char** ab = (char**)&"";
	int ntemp = 0;
	
	//加载器全局有效，不会人为删除
	//经由它加载的dll也不卸载，直到程序结束
	ExtensionLoader loadTools = ExtensionLoader();

	//------------------------------------------------------------------------------
	StandardParseBaseSupportInterface* basep=NULL;
	loadTools.LoadNewParseBaseExtension("Card_57_original_msg_parse_support.dll", ab, ntemp, &basep);

	//获取关键字全过程
	basep->EnumKeyWordsInner(&ab, &ntemp);
	printf("开始打印\n");
	for (int i = 0; i < ntemp; i++)
	{
		printf("%s\n", *(ab+i));
	}

	//---------------------------------------------------------------------------
	StandardExtensionInterface* pextension = NULL;
	//loadTools.LoadNewParseEnhanceExtension("OneWordAs_float.dll", ab, ntemp, &pextension);
	//loadTools.LoadNewParseEnhanceExtension("Code_mark_parse.dll", ab, ntemp, &pextension);
	loadTools.LoadNewParseEnhanceExtension("TwoWordAs_union.dll", ab, ntemp, &pextension);

	pextension->EnumKeyWordsInner(&ab, &ntemp);
	printf("打印插件选项\n");
	for (int i = 0; i < ntemp; i++)
	{
		printf("%s\n", *(ab + i));
	}





	return;

}