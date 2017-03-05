// 下列 ifdef 块是创建使从 DLL 导出更简单的  
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 STDINTERFACE_EXPORTS  
// 符号编译的。在使用此 DLL 的  
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将  
// STDINTERFACE_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的  
// 符号视为是被导出的。  


#ifdef STDINTERFACE_EXPORTS  
#define STDINTERFACE_API __declspec(dllexport)  
#else  
#define STDINTERFACE_API __declspec(dllimport)  
#endif  

#pragma once
#include "../MsgTranslateSolution/Macro_Global.h"
#include "AbstractPlugClass.h"

class StandardParseBaseSupportInterface :public AbstractPlugClass
{
public:
	~StandardParseBaseSupportInterface() {};

	// 根据传入的二维字符串数组获取总线消息中的信息，通过bufferOut返回信息，参与到软件主体的判断过程
	// 输入参数：msgArray,传入的软件主体获取的原始总线消息。
	// 输入参数：argv，传入的字符串数组,存储传入的参数。
	// 输入参数：bufferOut,处理后得到的内容通过此缓存区传出。插件需要自行解决字符串指针，
	//			传出来之后，需要长期保存指针值，不能直接释放掉
	virtual int GetKeyWords(const UWORD_i16* const msgArray , const char* const argv, char** bufferOut) = 0;

	// 提取基础解析服务模块所提供的所有消息解析方式
	// 输入参数：argsArrayOut,获取本模块提供的解析服务的所有方式。插件需要自行解决字符串指针，
	//			传出来之后，需要长期保存指针值，不能直接释放掉
	// 输入参数：argsCount，方式数量
	virtual int EnumKeyWordsInner(char*** argsArrayOut, int* argsCount) = 0;

	// 将纯消息内容从原始消息中提取出来。插件需要自行解决字符串指针，
	//			传出来之后，需要长期保存指针值，不能直接释放掉
	virtual int GetPureMsgBody(const UWORD_i16* const msgBufin, UWORD_i16 ** bufferOut) = 0;

	virtual int GetPlugTypeMsg(char ** bufferOut) {
		*bufferOut = "BaseSupport";
		return 0;
	}
	virtual int OpenBinaryDataFile(const char* const filePath) = 0;

	//返回值标识是否有值，是的话返回0，否则返回-1,用于标志是否结束
	//插件需要自行解决消息指针，传出来之后，需要长期保存指针值，不能直接释放掉
	virtual int GetOneOriginalMsg(UWORD_i16** bufferOut) = 0;
};


//导出对象指针，需要每个dll作者实现此函数，将派生类通过此函数导出
extern "C" STDINTERFACE_API StandardParseBaseSupportInterface* GetNewParseBaseInstancePtr(char** argv, int argc = 0);