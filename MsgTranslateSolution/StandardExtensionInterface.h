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



// 面向对象化的插件实现方式，相对于传统的C语言有结构清晰，行为明确的优点
// 每个插件必须暴漏的基本接口
class StandardExtensionInterface:public AbstractPlugClass
{
public:
	// 抽象类的虚析构函数 
	virtual ~StandardExtensionInterface() {}; 

	// 通过此函数更好的处理消息翻译问题，传递参数是第一个待处理消息字第一个字的指针,传出参数为翻译的消息结果
	virtual int ProcessMsgUnit(const UWORD_i16* const ptr_value_first, const char* const args, char** bufferOut) = 0;

	// 列举所有可选参数
	virtual int EnumKeyWordsInner(char*** argsArrayOut, int* argsCount) = 0;

	virtual int GetPlugTypeMsg(char ** bufferOut) {
		*bufferOut = "EnhancePlug";
		return 0;
	}

};

// 连接动态链接库插件与解析器的一级接口，每个动态dll都需要实现这个接口函数，将插件类导入程序
extern "C" STDINTERFACE_API StandardExtensionInterface* GetNewParseExtensionInstancePtr(char** argv, int argc = 0);

