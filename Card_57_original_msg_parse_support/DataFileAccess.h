#pragma once
class DataFileAccess {
public:
	DataFileAccess();
	virtual ~DataFileAccess();
	virtual int initSelf(const char* const filepath);
private:
	FILE* file;
public:
	virtual int GetAMsgFromDataFile(UWORD_i16** msg_out);
private:
	bool WetherEOF;
	UWORD_i16 msg_cache[200];
	int headJ;
};

