#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

#define N 20
typedef struct Player
{
	int num;		//编号
	char name[N];	//姓名
	float score[10];//10位评委打分
}Play;

typedef struct Manage
{
	Play p;
	float avgScore;
	float sumScore;
}Man;


int count = 0;		//选手个数
Man manage[1024];	//管理数组

//输入选手基本信息
void input()
{
	int choice;
	while (1)
	{
		printf("输入选手%d的姓名：", count + 1);
		scanf("%s", manage[count].p.name);
		printf("输入选手%d的编号：", count + 1);
		scanf("%d", &manage[count].p.num);
		printf("是否继续？(0:否  1:是)：");
		count++;
		scanf("%d", &choice);
		if (choice == 0)
			break;
	}
}

//评委打分
void mark()
{
	int i,j;
	float max = -1, min = 101;
	for (i = 0; i < count; ++i)
	{
		printf("选手%d\n", i + 1);
		for (j = 0; j < 10; ++j)
		{
			printf("输入评委%d的分数：", j + 1);
			scanf("%f", &manage[i].p.score[j]);
			if (manage[i].p.score[j] > max)
				max = manage[i].p.score[j];
			if (manage[i].p.score[j] < min)
				min = manage[i].p.score[j];
			manage[i].sumScore += manage[i].p.score[j];
		}
		manage[i].sumScore -= (max + min);
		manage[i].avgScore = manage[i].sumScore / 10;
	}
}

void copy(Man *a, Man *b)
{
	int i;
	strcpy(a->p.name, b->p.name);
	a->avgScore = b->avgScore;
	a->sumScore = b->sumScore;
	a->p.num = b->p.num;
	for (i = 0; i < 10; ++i)
		a->p.score[i] = b->p.score[i];
}

//成绩排序(按平均分)
void sort()
{
	int i,j;
	for (i = 0; i < count - 1; ++i)
		for (j = 0; j < count - 1 - i; ++j)
			if (manage[j].avgScore > manage[j + 1].avgScore)
			{
				Man temp;
				copy(&temp, &manage[j]);
				copy(&manage[j], &manage[j + 1]);
				copy(&manage[j + 1], &temp);
			}
	printf("排序完成！\n");
}

//数据查询(按编号)
void query()
{
	int _num, tag = 0 , i,j;
	printf("输入编号：");
	scanf("%d", &_num);
	for (i = 0; i < count; ++i)
	{
		if (manage[i].p.num == _num)
		{
			tag = 1;
			printf("编号：%d\n", manage[i].p.num);
			printf("姓名：%s\n", manage[i].p.name);
			printf("平均分：%.2f\n", manage[i].avgScore);
			printf("总分：%.2f\n", manage[i].sumScore);
			printf("十个评委的分数\n");
			for (j = 0; j < 10; ++j)
			{
				printf("%.2f\t", manage[i].p.score[j]);
				if (j == 4)
					printf("\n");
			}
		}
	}
	if (!tag)
		printf("没有找到此人！\n");
}

//追加数据
void append()
{
	input();
}

//写入数据文件
void write()
{
	FILE *fp;
	if ((fp = fopen("info.dat", "wb")) == NULL)
	{
		printf("文件写入失败！\n");
		return;
	}

	fwrite(manage, sizeof(Man), count, fp);
	fclose(fp);
}

void menu()
{
	int choice,i;
	const char title[7][1024] = {
		"输入选手数据","评委打分",
		"成绩排序(按平均分)",
		"数据查询","追加数据",
		"写入数据文件","退出"
	};
	
	while (1)
	{
		system("cls");
		printf("*****歌手比赛系统*****\n");
		for (i = 0; i < 7; ++i)
			printf("\t[%d]%s\n", i + 1, title[i]);
		printf("输入选择(1 - 7)：");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:input();
			break;
		case 2:mark();
			break;
		case 3:sort();
			break;
		case 4:query();
			break;
		case 5:append();
			break;
		case 6:write();
			break;
		case 7:return;
			break;
		default:printf("输入错误！\n");
			break;
		}
		system("pause");
	}
}

int main()
{
	menu();
	return 0;
}
