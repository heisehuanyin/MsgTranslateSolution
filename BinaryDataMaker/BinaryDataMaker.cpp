// BinaryDataMaker.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int main()
{
	FILE* binaryFile = nullptr;
	
	fopen_s(&binaryFile,"..\\Debug\\busmsg_simulate_datafile.dat","wb");

	int msgCount = -1;

	while (msgCount < 20)
	{
		++msgCount;
		printf("Now,the %dth rows data has been made.\n", msgCount);
		int ttss = 0xaa55aa55;
		fwrite(&ttss, sizeof(char), 4, binaryFile);

		int tttemp = (msgCount & 0xff) << 24;//帧计数
		tttemp = ((msgCount & 0xff00) << 8 ) | tttemp;
		tttemp = ((msgCount & 0xff0000) >> 8) | tttemp;
		tttemp = ((msgCount & 0xff000000) >> 24) | tttemp;
		fwrite(&tttemp, sizeof(char), 4, binaryFile);

		int sddd = 222052360;//系统时标
		tttemp = (sddd & 0xff) << 24;
		tttemp = ((sddd & 0xff00) << 8) | tttemp;
		tttemp = ((sddd & 0xff0000) >> 8) | tttemp;
		tttemp = ((sddd & 0xff000000) >> 24) | tttemp;
		fwrite(&tttemp, sizeof(char), 4, binaryFile);

		//MT状态字
		ttss = 0x0081;
		fwrite(&ttss, sizeof(char), 2, binaryFile);

		//1553B时标
		ttss = 0x3979;
		fwrite(&ttss, sizeof(char), 2, binaryFile);

		//数据指针
		ttss = 0x00;
		fwrite(&ttss, sizeof(char), 2, binaryFile);

		union {
			float fdata;
			unsigned short sdata[2];
		}ls;
		union {
			int idata;
			unsigned short sdata[2];
		}iv;

		switch (msgCount % 4)
		{
		case 0://BC->RT
			ttss = 0x2578;
			fwrite(&ttss, sizeof(char), 2, binaryFile);
			//purmsg====================================================
			ttss = 0x0a01;
			fwrite(&ttss, sizeof(char), 2, binaryFile);

			//日期，三字，总线数据字形表示法，利用Code_mark_parse解析
			ttss = 0x2017;
			fwrite(&ttss, sizeof(char), 2, binaryFile);

			ttss = 0x0228;
			fwrite(&ttss, sizeof(char), 2, binaryFile);

			ttss = 0x1253;
			fwrite(&ttss, sizeof(char), 2, binaryFile);

			ttss = 0x2578;
			fwrite(&ttss, sizeof(char), 2, binaryFile);

			////////////////////////////////////////////////////////////////
			ttss = 0x0078;
			fwrite(&ttss, sizeof(char), 2, binaryFile);
		case 1://RT->RT
			ttss = 0x6051;
			fwrite(&ttss, sizeof(char), 2, binaryFile);
			ttss = 0xc00c;
			fwrite(&ttss, sizeof(char), 2, binaryFile);
			ttss = 0xdbfe;
			fwrite(&ttss, sizeof(char), 2, binaryFile);
			//purmsg===========================================

			ttss = 0x0a02;
			fwrite(&ttss, sizeof(char), 2, binaryFile);

			//单个字表示浮点数，比率100,真实值12.75
			ttss = 0x4FB;
			fwrite(&ttss, sizeof(char), 2, binaryFile);

			//两个字代表一个浮点数 22.5，高字节在前
			
			ls.fdata = 22.5;

			ttss = ls.sdata[0];
			fwrite(&ttss, sizeof(char), 2, binaryFile);

			ttss = ls.sdata[1];
			fwrite(&ttss, sizeof(char), 2, binaryFile);






			//两个字代表一个整形 220， 高字节在前
			
			iv.idata = 220;

			ttss = iv.sdata[0];
			fwrite(&ttss, sizeof(char), 2, binaryFile);

			ttss = iv.sdata[1];
			fwrite(&ttss, sizeof(char), 2, binaryFile);







			ttss = 0x2578;
			fwrite(&ttss, sizeof(char), 2, binaryFile);

			ttss = 0x2578;
			fwrite(&ttss, sizeof(char), 2, binaryFile);

			ttss = 0x2578;
			fwrite(&ttss, sizeof(char), 2, binaryFile);

			ttss = 0x2578;
			fwrite(&ttss, sizeof(char), 2, binaryFile);

			ttss = 0x2578;
			fwrite(&ttss, sizeof(char), 2, binaryFile);

			ttss = 0x2578;
			fwrite(&ttss, sizeof(char), 2, binaryFile);

			ttss = 0x2578;
			fwrite(&ttss, sizeof(char), 2, binaryFile);

			ttss = 0x2578;
			fwrite(&ttss, sizeof(char), 2, binaryFile);

			ttss = 0x2578;
			fwrite(&ttss, sizeof(char), 2, binaryFile);

			ttss = 0x2578;
			fwrite(&ttss, sizeof(char), 2, binaryFile);

			ttss = 0x2578;
			fwrite(&ttss, sizeof(char), 2, binaryFile);

			ttss = 0x2578;
			fwrite(&ttss, sizeof(char), 2, binaryFile);

			ttss = 0x2578;
			fwrite(&ttss, sizeof(char), 2, binaryFile);

			ttss = 0x2578;
			fwrite(&ttss, sizeof(char), 2, binaryFile);

			ttss = 0x2578;
			fwrite(&ttss, sizeof(char), 2, binaryFile);

			ttss = 0x2578;
			fwrite(&ttss, sizeof(char), 2, binaryFile);

			ttss = 0x2578;
			fwrite(&ttss, sizeof(char), 2, binaryFile);

			ttss = 0x2578;
			fwrite(&ttss, sizeof(char), 2, binaryFile);

			ttss = 0x2578;
			fwrite(&ttss, sizeof(char), 2, binaryFile);

			ttss = 0x2578;
			fwrite(&ttss, sizeof(char), 2, binaryFile);

			ttss = 0x2578;
			fwrite(&ttss, sizeof(char), 2, binaryFile);

			ttss = 0x2578;
			fwrite(&ttss, sizeof(char), 2, binaryFile);

			ttss = 0x2578;
			fwrite(&ttss, sizeof(char), 2, binaryFile);

			ttss = 0x2578;
			fwrite(&ttss, sizeof(char), 2, binaryFile);

			ttss = 0x2578;
			fwrite(&ttss, sizeof(char), 2, binaryFile);

			ttss = 0x2578;
			fwrite(&ttss, sizeof(char), 2, binaryFile);

			//////////////////////////////////////////////////////////////////
			ttss = 0x0078;
			fwrite(&ttss, sizeof(char), 2, binaryFile);
		case 2://RT->BC
			ttss = 0x4054;
			fwrite(&ttss, sizeof(char), 2, binaryFile);
			ttss = 0x0050;
			fwrite(&ttss, sizeof(char), 2, binaryFile);
			//purmsg===========================================

			ttss = 0x0a03;
			fwrite(&ttss, sizeof(char), 2, binaryFile);

			//单个字表示浮点数，比率100,真实值32.64
			ttss = 0xcc0;
			fwrite(&ttss, sizeof(char), 2, binaryFile);

			//两个字代表一个浮点数 45.6，高字节在前
			ls.fdata =(float) 45.6;

			ttss = ls.sdata[0];
			fwrite(&ttss, sizeof(char), 2, binaryFile);

			ttss = ls.sdata[1];
			fwrite(&ttss, sizeof(char), 2, binaryFile);






			//两个字代表一个整形 230， 高字节在前
			iv.idata = 230;

			ttss = iv.sdata[0];
			fwrite(&ttss, sizeof(char), 2, binaryFile);

			ttss = iv.sdata[1];
			fwrite(&ttss, sizeof(char), 2, binaryFile);







			ttss = 0x2578;
			fwrite(&ttss, sizeof(char), 2, binaryFile);

			ttss = 0x2578;
			fwrite(&ttss, sizeof(char), 2, binaryFile);

			ttss = 0x2578;
			fwrite(&ttss, sizeof(char), 2, binaryFile);

			ttss = 0x2578;
			fwrite(&ttss, sizeof(char), 2, binaryFile);

			ttss = 0x2578;
			fwrite(&ttss, sizeof(char), 2, binaryFile);

			ttss = 0x2578;
			fwrite(&ttss, sizeof(char), 2, binaryFile);

			ttss = 0x2578;
			fwrite(&ttss, sizeof(char), 2, binaryFile);

			ttss = 0x2578;
			fwrite(&ttss, sizeof(char), 2, binaryFile);

			ttss = 0x2578;
			fwrite(&ttss, sizeof(char), 2, binaryFile);

			ttss = 0x2578;
			fwrite(&ttss, sizeof(char), 2, binaryFile);

			ttss = 0x2578;
			fwrite(&ttss, sizeof(char), 2, binaryFile);

			ttss = 0x2578;
			fwrite(&ttss, sizeof(char), 2, binaryFile);

			ttss = 0x2578;
			fwrite(&ttss, sizeof(char), 2, binaryFile);

			ttss = 0x2578;
			fwrite(&ttss, sizeof(char), 2, binaryFile);

			ttss = 0x2578;
			fwrite(&ttss, sizeof(char), 2, binaryFile);

			ttss = 0x2578;
			fwrite(&ttss, sizeof(char), 2, binaryFile);

			ttss = 0x2578;
			fwrite(&ttss, sizeof(char), 2, binaryFile);

			ttss = 0x2578;
			fwrite(&ttss, sizeof(char), 2, binaryFile);

			ttss = 0x2578;
			fwrite(&ttss, sizeof(char), 2, binaryFile);

			ttss = 0x2578;
			fwrite(&ttss, sizeof(char), 2, binaryFile);

			ttss = 0x2578;
			fwrite(&ttss, sizeof(char), 2, binaryFile);

			ttss = 0x2578;
			fwrite(&ttss, sizeof(char), 2, binaryFile);

			ttss = 0x2578;
			fwrite(&ttss, sizeof(char), 2, binaryFile);

			ttss = 0x2578;
			fwrite(&ttss, sizeof(char), 2, binaryFile);

			ttss = 0x2578;
			fwrite(&ttss, sizeof(char), 2, binaryFile);

			ttss = 0x2578;
			fwrite(&ttss, sizeof(char), 2, binaryFile);

			//////////////////////////////////////////////////////////////////

		default://矢量字
			ttss = 0x107c;
			fwrite(&ttss, sizeof(char), 2, binaryFile);
			ttss = 0x0078;
			fwrite(&ttss, sizeof(char), 2, binaryFile);
			ttss = 0x0022;
			fwrite(&ttss, sizeof(char), 2, binaryFile);
			break;
		}
	}


    return 0;
}

