// PassWordBook.cpp : 定义控制台应用程序的入口点。
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
	int nNum; //PASSWORDBOOK的编号

}PASSWORDBOOK;

void searchAllInfo();
void addPwd();
void delPwd();
void changePwd();
void searchInfo();
void saveInfo();
void readInfo();

int g_nCount;//当前用到多少个堆内存
int g_nNum;//总共申请的堆内存

PASSWORDBOOK *g_pBook = NULL;

int main()
{
	g_nNum = 0;
	g_nCount = 0;

	readInfo();
	
	while (1)
	{
		printf("1 查看所有密码:\n");
		printf("2 新增密码:\n");
		printf("3 删除密码:\n");
		printf("4 修改密码:\n");
		printf("5 查询密码:\n");
		printf("请输入你的选择:\n");

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
			printf("输入有误，请重新输入\n");
			break;
		}
		
	}
    return 0;
}

//查询所有
void searchAllInfo() {

	for (int i = 0; i < g_nCount; ++i)
	{
		printf("第%d个信息:\n", (g_pBook + i)->nNum + 1);
		printf("网址:%s\n", (g_pBook + i)->szWebSite);
		printf("账号:%s\n", (g_pBook + i)->szAccount);
		printf("密码:%s\n", (g_pBook + i)->szPwd);
	}
	
	system("pause");
	system("cls");
}

//新增
void addPwd() {

	if (g_nNum <= g_nCount) {
		g_pBook = (PASSWORDBOOK*)realloc(g_pBook, sizeof(PASSWORDBOOK) * (g_nNum +1));
		++g_nNum;
	}
	
	printf("请输入网址:\n");
	scanf_s("%s", &(g_pBook + g_nCount)->szWebSite,32);
	printf("请输入账号:\n");
	scanf_s("%s", &(g_pBook + g_nCount)->szAccount,32);
	printf("请输入密码:\n");
	scanf_s("%s", &(g_pBook + g_nCount)->szPwd, 32);
	printf("输入成功\n");

	(g_pBook + g_nCount)->nNum = g_nCount;

	g_nCount++;

	saveInfo();

	Sleep(1000);
	system("cls");
}

//删除
void delPwd() {
	char szWebSite[32] = { 0 };
	printf("请输入要删除的网址\n");
	scanf_s("%s", &szWebSite, sizeof(szWebSite));

	//找到需要删除的网站的位置，将后面的数据往前覆盖
	for (int i = 0; i < g_nCount - 1; ++i)
	{
		if (strcmp((g_pBook + i)->szWebSite, szWebSite) == 0) {
			strcpy_s((g_pBook + i)->szWebSite, (g_pBook + i + 1)->szWebSite);
			strcpy((g_pBook + i)->szAccount, (g_pBook + i + 1)->szAccount);
			strcpy((g_pBook + i)->szPwd, (g_pBook + i + 1)->szPwd);
			(g_pBook + i)->nNum--;
		}
	}

	//最后一个结构体清空数据
	strcpy((g_pBook + (g_nCount - 1))->szWebSite, "");
	strcpy((g_pBook + (g_nCount - 1))->szAccount, "");
	strcpy((g_pBook + (g_nCount - 1))->szPwd, "");
	(g_pBook + g_nCount - 1)->nNum = 0;

	--g_nCount;

	saveInfo();

	printf("删除成功\n");
	system("pause");
	system("cls");
}

//修改
void changePwd() {
	char szWebSite[32] = { 0 };
	char szNewPwd[32] = { 0 };
	printf("请输入要修改密码的网站\n");
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
		printf("输入网址错误\n");
	}
	else {
		printf("请输入新密码\n");
		scanf_s("%s", &szNewPwd, sizeof(szNewPwd));
		strcpy(pwd->szPwd, szNewPwd);
		printf("修改成功\n");
	}

	saveInfo();
	
	Sleep(1000);
	system("cls");
}

//查询
void searchInfo() {
	char szWebSite[32] = { 0 };
	printf("请输入需要查询的网站\n");
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
		printf("查询失败");
	}
	else {
		printf("网站:%s\n", pwd->szWebSite);
		printf("账号:%s\n", pwd->szAccount);
		printf("密码:%s\n", pwd->szPwd);
	}

	system("pause");
	system("cls");
}
//将输入的信息保存到二进制文件
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
//读取二进制文件
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