// PassWordBook.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <stdlib.h>
#include <malloc.h>
#include <windows.h>

typedef struct _PassWordBook
{
	char szWebSite[32];
	char szAccount[32];
	char szPwd[32];
	int nNum; //PASSWORDBOOK�ı��

}PASSWORDBOOK;

void searchAllInfo();
void addPwd();
void delPwd();
void changePwd();
void searchInfo();
void saveInfo();
void readInfo();

int g_nCount;//��ǰ�õ����ٸ����ڴ�
int g_nNum;//�ܹ�����Ķ��ڴ�

PASSWORDBOOK *g_pBook = NULL;

int main()
{
	g_nNum = 0;
	g_nCount = 0;

	readInfo();
	
	while (1)
	{
		printf("1 �鿴��������:\n");
		printf("2 ��������:\n");
		printf("3 ɾ������:\n");
		printf("4 �޸�����:\n");
		printf("5 ��ѯ����:\n");
		printf("���������ѡ��:\n");

		int option;
		scanf_s("%d", &option);

		switch (option)
		{
		case 1:
			searchAllInfo();
			break;
		case 2:
			addPwd();
			break;;
		case 3:
			delPwd();
			break;
		case 4:
			changePwd();
			break;
		case 5:                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
			break;
		default:
			printf("������������������\n");
			break;
		}
		
	}
    return 0;
}

//��ѯ����
void searchAllInfo() {

	for (int i = 0; i < g_nCount; ++i)
	{
		printf("��%d����Ϣ:\n", (g_pBook + i)->nNum + 1);
		printf("��ַ:%s\n", (g_pBook + i)->szWebSite);
		printf("�˺�:%s\n", (g_pBook + i)->szAccount);
		printf("����:%s\n", (g_pBook + i)->szPwd);
	}
	
	system("pause");
	system("cls");
}

//����
void addPwd() {

	if (g_nNum <= g_nCount) {
		g_pBook = (PASSWORDBOOK*)realloc(g_pBook, sizeof(PASSWORDBOOK) * (g_nNum +1));
		++g_nNum;
	}
	
	printf("��������ַ:\n");
	scanf_s("%s", &(g_pBook + g_nCount)->szWebSite,32);
	printf("�������˺�:\n");
	scanf_s("%s", &(g_pBook + g_nCount)->szAccount,32);
	printf("����������:\n");
	scanf_s("%s", &(g_pBook + g_nCount)->szPwd, 32);
	printf("����ɹ�\n");

	(g_pBook + g_nCount)->nNum = g_nCount;

	g_nCount++;

	saveInfo();

	Sleep(1000);
	system("cls");
}

//ɾ��
void delPwd() {
	char szWebSite[32] = { 0 };
	printf("������Ҫɾ������ַ\n");
	scanf_s("%s", &szWebSite, sizeof(szWebSite));

	//�ҵ���Ҫɾ������վ��λ�ã��������������ǰ����
	for (int i = 0; i < g_nCount - 1; ++i)
	{
		if (strcmp((g_pBook + i)->szWebSite, szWebSite) == 0) {
			strcpy_s((g_pBook + i)->szWebSite, (g_pBook + i + 1)->szWebSite);
			strcpy((g_pBook + i)->szAccount, (g_pBook + i + 1)->szAccount);
			strcpy((g_pBook + i)->szPwd, (g_pBook + i + 1)->szPwd);
			(g_pBook + i)->nNum--;
		}
	}

	//���һ���ṹ���������
	strcpy((g_pBook + (g_nCount - 1))->szWebSite, "");
	strcpy((g_pBook + (g_nCount - 1))->szAccount, "");
	strcpy((g_pBook + (g_nCount - 1))->szPwd, "");
	(g_pBook + g_nCount - 1)->nNum = 0;

	--g_nCount;

	saveInfo();

	printf("ɾ���ɹ�\n");
	system("pause");
	system("cls");
}

//�޸�
void changePwd() {
	char szWebSite[32] = { 0 };
	char szNewPwd[32] = { 0 };
	printf("������Ҫ�޸��������վ\n");
	scanf_s("%s", &szWebSite, sizeof(szWebSite));
	
	PASSWORDBOOK *pwd = NULL;
	for (int i = 0; i < g_nCount; ++i)
	{
		if (strcmp((g_pBook + i)->szWebSite, szWebSite) == 0) {
			pwd = g_pBook + i;
			break;
		}
	}

	if (NULL == pwd) {
		printf("������ַ����\n");
	}
	else {
		printf("������������\n");
		scanf_s("%s", &szNewPwd, sizeof(szNewPwd));
		strcpy(pwd->szPwd, szNewPwd);
		printf("�޸ĳɹ�\n");
	}

	saveInfo();
	
	Sleep(1000);
	system("cls");
}

//��ѯ
void searchInfo() {
	char szWebSite[32] = { 0 };
	printf("��������Ҫ��ѯ����վ\n");
	scanf_s("%s", &szWebSite, sizeof(szWebSite));

	PASSWORDBOOK *pwd = NULL;

	for (int i = 0; i < g_nCount; ++i)
	{
		if (strcmp((g_pBook + i)->szWebSite, szWebSite) == 0) {
			pwd = g_pBook + i;
			break;
		}
	}

	if (NULL == pwd) {
		printf("��ѯʧ��");
	}
	else {
		printf("��վ:%s\n", pwd->szWebSite);
		printf("�˺�:%s\n", pwd->szAccount);
		printf("����:%s\n", pwd->szPwd);
	}

	system("pause");
	system("cls");
}
//���������Ϣ���浽�������ļ�
void saveInfo() {
	FILE *pFile = NULL;
	fopen_s(&pFile, "./pwd.txt", "wb");

	fwrite(&g_nCount, sizeof(g_nCount), 1, pFile);
	fwrite(&g_nNum, sizeof(g_nNum),1, pFile);

	int byteSize = sizeof(PASSWORDBOOK)*g_nNum;
	char *buf = (char*)malloc(byteSize);
	memcpy_s(buf, byteSize, g_pBook, byteSize);

	for (unsigned int i = 0; i < byteSize; ++i)
	{
		buf[i] ^= 5;
	}

	fwrite(buf, sizeof(PASSWORDBOOK), g_nNum, pFile);

	fclose(pFile);
}
//��ȡ�������ļ�
void readInfo() {

	FILE  *pFile = NULL;
	errno_t err= fopen_s(&pFile, "./pwd.txt", "rb");

	if (err != 0) {
		return;
	}

	fread(&g_nCount, sizeof(g_nCount), 1, pFile);
	fread(&g_nNum, sizeof(g_nNum), 1, pFile);

	g_pBook = (PASSWORDBOOK*)malloc(sizeof(PASSWORDBOOK)*g_nNum);

	memset(g_pBook, 0, sizeof(PASSWORDBOOK)*g_nNum);

	fread(g_pBook, sizeof(PASSWORDBOOK), g_nNum, pFile);

	int byteSize = sizeof(PASSWORDBOOK)*g_nNum;
	char *buf = (char *)g_pBook;

	for (size_t i = 0; i < byteSize; ++i)
	{
		buf[i] ^= 5;
	}
	fclose(pFile);
}