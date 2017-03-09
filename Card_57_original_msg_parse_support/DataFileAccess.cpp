#include "stdafx.h"
#include "DataFileAccess.h"


DataFileAccess::DataFileAccess() : file(NULL), WetherEOF(false), headJ(0) {
	
}


DataFileAccess::~DataFileAccess() {
	fclose(this->file);
}


int DataFileAccess::initSelf(const char* const filepath) {
	
	fopen_s(&this->file, filepath, "rb");

	for (int i = 0; i < 200; i++) {
		msg_cache[i] = 0;
	}

	UWORD_i16 msgu[2] = {0};
	fread_s(msgu, 2, sizeof(UWORD_i16), 1, this->file);
	fread_s(msgu, 2, sizeof(UWORD_i16), 1, this->file);

	return 0;
}


int DataFileAccess::GetAMsgFromDataFile(UWORD_i16** msg_out) {
	if (this->WetherEOF) {
		return -1;//已经结束，此次没有消息数值
	}

	//清空数组
	for (int i = 0; i < 200; i++) {
		if (i<2) {
			msg_cache[i] = 0x55aa;
		}
		else {
			msg_cache[i] = 0;
		}
	}

	
	UWORD_i16 msgu[2] = {0};
	int looptimes = 1;

	while (looptimes < 200 ) {
		++looptimes;

		fread_s(msgu, 2, sizeof(UWORD_i16), 1, this->file);

		this->msg_cache[looptimes] = msgu[0];

		if (msgu[0] == 0x55aa) {
			this->headJ += 1;
		}
		
		if (this->headJ == 2 || feof(this->file) != 0) {
			this->headJ = 0;
			break;
		}
	}

	if (looptimes == 200 || feof(this->file) != 0) {//文件结束，或者是最后一条消息的时候，置位
		this->WetherEOF = true;
	}

	*msg_out = this->msg_cache;

	return 0;
}

