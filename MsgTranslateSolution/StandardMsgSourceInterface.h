#ifdef STDINTERFACE_EXPORTS  
#define STDINTERFACE_API __declspec(dllexport)  
#else  
#define STDINTERFACE_API __declspec(dllimport)  
#endif  

#pragma once

#include "../MsgTranslateSolution/Macro_Global.h"


class StandardMsgSourceInterface
{
public:
	~StandardMsgSourceInterface() {};

	// 调用此函数立刻打开制定的数据文件，如果有文件处于打开状态首先会关闭文件句柄，一切状态都会刷新
	virtual int OpenOneDataFileAtNow(const char* const DataFilePath) = 0;

	// 获取一条原始格式的总线消息
	virtual int OriginalFormat_PickOneMsg(UWORD_i16** MsgArray_Ptr) = 0;

};



// 连接动态链接库插件与解析器的一级接口，每个动态dll都需要实现这个接口函数，将插件类导入程序
extern "C" STDINTERFACE_API StandardMsgSourceInterface* GetNewMsgSourceInstancePtr(char** argv, int argc = 0);
