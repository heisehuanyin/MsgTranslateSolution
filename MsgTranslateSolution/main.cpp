/**������2017��02��23��
***����Ԫ������Ҫ���ڸ��ٷ���1553B������Ϣ
***�������1553B����Э���ļ�����������
***/

#include <iostream>
#include "StandardParseBaseSupportInterface.h"
#include "StandardExtensionInterface.h"
#include <Windows.h>
#include "ExtensionLoader.h"




//���ڷ��빤���������
//���������argc�������ĸ���
//���������argv������
//��ʽ������ MsgTranslateSolution  /base xxxx.xml   /source xxxx.dat     /group dm_group
//���������� ��������			   ָ�������׼		ָ����Ϣ��¼�ļ�	 ָ���������
//��ʽ������ MsgTranslateSolution  /help
//���������� ��������			   ��Ҫ�����а���
void main(int argc, char** argv) {
	//����ѡ���ӡ��������
	if (strcmp(*(argv + 1), "/help") == 0) {
		printf("��ʽ������ MsgTranslateSolution  /base xxxx.xml   /source xxxx.dat     /group dm_group\n���������� ��������		ָ�������׼	ָ����Ϣ��¼�ļ�	ָ���������\n��ʽ������ MsgTranslateSolution  /help\n���������� ��������		��Ҫ�����а���\n");
		return;
	}

	//����ѡ��2����ӡ���������ѡ��
	// ������

	// loadPlug
	char** ab = (char**)&"";
	int ntemp = 0;
	
	//������ȫ����Ч��������Ϊɾ��
	//���������ص�dllҲ��ж�أ�ֱ���������
	ExtensionLoader loadTools = ExtensionLoader();

	//------------------------------------------------------------------------------
	StandardParseBaseSupportInterface* basep=NULL;
	loadTools.LoadNewParseBaseExtension("Card_57_original_msg_parse_support.dll", ab, ntemp, &basep);

	//��ȡ�ؼ���ȫ����
	basep->EnumKeyWordsInner(&ab, &ntemp);
	printf("��ʼ��ӡ\n");
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
	printf("��ӡ���ѡ��\n");
	for (int i = 0; i < ntemp; i++)
	{
		printf("%s\n", *(ab + i));
	}





	return;

}