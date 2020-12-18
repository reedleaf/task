#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int a, b;
int N = 1;
double highRecord[4] = {0};

void load();
void save(const char* fileName, const char* openMode, double operand);
//产生随机数
void createRand(int n)
{
	srand((unsigned int)time(NULL));
	switch (n)
	{
	case 1:
		a = rand() % 11;
		b = rand() % 11;
		break;
	case 2:
		a = rand() % 21;
		b = rand() % 21;
		break;
	case 3:
		a = rand() % 51;
		b = rand() % 51;
		break;
	case 4:
		a = rand() % 100 + 1;
		b = rand() % 100 + 1;
		break;
	default:printf("输入错误！");
		break;
	}
}
//选择范围菜单
void randMenu()
{
	printf("【1】10以内\n");
	printf("【2】20以内\n");
	printf("【3】50以内\n");
	printf("【4】100以内\n");
	scanf("%d", &N);
	createRand(N);
}

//运算
void operation(int n,char c)
{
	int  count = 0, correct = 0, answer;
	char ch;
	while (1)
	{
		createRand(N);
		if (n == 4)
			printf("除法取整数\n");
		printf("%d %c %d = ", a, c, b);
		scanf("%d", &answer);
		if (n == 1 && a + b == answer)
			correct++;
		else if(n == 2 && a - b == answer)
			correct++;
		else if (n == 3 && a * b == answer)
			correct++;
		else if (n == 4 && a / b == answer)
			correct++;
		count++;
		printf("是否继续?(y or n)：");
		getchar();
		scanf("%c", &ch);
		if (ch == 'n' || ch == 'N')
			break;
	}
	double record = (float)correct / count * 100;
	printf("本次练习的准确率为：%.2f%%\n", record);
	load();
	if (record > highRecord[n - 1])
	{
		highRecord[n - 1] = record;
		if (n == 1)
			printf("加法中取得了最高分\n");
		if (n == 2)
			printf("减法打败了所有人！！！！\n");
		if (n == 3)
			printf("乘法学的很好哦！\n");
		if (n == 4)
			printf("无人能敌的除法！\n");
	}
	save("score.txt", "a",record);
	save("high.txt", "w",0);
}

//读取记录
void load()
{
	FILE  *fp;
	if ((fp = fopen("high", "r")) == NULL)
		return;
	fscanf(fp, "%lf%lf%lf%lf", &highRecord[0], &highRecord[1], &highRecord[2], &highRecord[3]);
	fclose(fp);
}
//写入记录
void save(const char* fileName,const char* openMode,double operand)
{
	FILE *fp;
	if ((fp = fopen(fileName, openMode)) == NULL)
	{
		printf("文件打开失败！\n");
		return;
	}
	if (fileName == "score.txt")
		fprintf(fp, "%.2lf\n", operand);
	else
		fprintf(fp, "%.2lf\t%.2lf\t%.2lf\t%.2lf\n", highRecord[0], highRecord[1], highRecord[2], highRecord[3]);
	fclose(fp);
}
//子菜单
void childMenu()
{
	while (1)
	{
		system("cls");
		int choice;
		printf("【0】返回上级菜单\n");
		printf("【1】加法练习\n");
		printf("【2】减法练习\n");
		printf("【3】乘法练习\n");
		printf("【4】除法练习\n");
		scanf("%d", &choice);
		switch (choice)
		{
		case 0:
			return;
		case 1:operation(choice, '+');
			break;
		case 2:operation(choice, '-');
			break;
		case 3:operation(choice, '*');
			break;
		case 4:operation(choice, '/');
			break;
		default:printf("输入错误\n");
			break;
		}
		system("pause");
	}
}
//主菜单
void menu()
{
	int choice;
	while (1)
	{
		system("cls");
		printf("----小学生算术练习系统----\n");
		printf("【0】退出系统\n");
		printf("【1】算术练习\n");
		printf("【2】选择范围\n");
		scanf("%d", &choice);
		if (choice == 0)
			break;
		else if (choice == 1)
			childMenu();
		else if (choice == 2)
			randMenu();
		else
			printf("输入错误！\n");
	}
}

int main()
{
	menu();
	return 0;
}
