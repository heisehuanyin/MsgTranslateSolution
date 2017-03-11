#pragma once
#include "Macro_Global.h"

class AbstractPlugClass
{
public:
	virtual int GetPlugTypeMsg(char** BufferOut)=0;


	// 根据传入的二维字符串数组获取总线消息中的信息，通过bufferOut返回信息，参与到软件主体的判断过程
	// 输入参数：ptr_value_first,传入的软件主体获取的原始总线消息。
	// 输入参数：argv，传入的字符串数组,存储传入的参数。
	// 输入参数：bufferOut,处理后得到的内容通过此缓存区传出。插件需要自行解决字符串指针，
	//			传出来之后，需要长期保存指针值，不能直接释放掉
	virtual int ProcessMsgUnitAsHexOrStr(const UWORD_i16* const ptr_value_first, const char* const argv, char** bufferOut) = 0;

};

