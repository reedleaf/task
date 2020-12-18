#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Employee {
	char name[20];			//姓名
	int id;							//id
	float baseWage;		//基本工资
	float allowance;		//岗位津贴
	float insurance;		//医疗保险
}Emp;

int count = 0;				//记录个数
Emp manager[1024];//信息保存数组
 
//信息录入
void input()
{
	int choice;
	while (1)//循环输入,直接用户选择退出
	{
		printf("输入姓名：");
		scanf("%s", manager[count].name);
		printf("输入id：");
		scanf("%d", &manager[count].id);
		printf("输入基本工资：");
		scanf("%f", &manager[count].baseWage);
		printf("输入岗位津贴：");
		scanf("%f", &manager[count].allowance);
		printf("输入医疗保险：");
		scanf("%f", &manager[count].insurance);
		count++;
		printf("是否继续？(0:否 1:是)：");
		scanf("%d", &choice);
		if (choice == 0)
			break;
	}
}

//打印
void print(int i)
{
	printf("***********员工%d************\n", i + 1);
	printf("姓名：%s\n", manager[i].name);
	printf("ID：%d\n", manager[i].id);
	printf("基本工资：%.2f\n", manager[i].baseWage);
	printf("岗位津贴：%.2f\n", manager[i].allowance);
	printf("医疗保险：%.2f\n", manager[i].insurance);
}
//显示记录
void show()
{
	int i;
	//循环打印所有信息
	for (i = 0; i < count; ++i)
		print(i);
}
//查找id，修改和查询都要用，单独拿出来
int find()
{
	int _id, i;
	printf("输入职工的id：");
	scanf("%d", &_id);
	for (i = 0; i < count; ++i)
		if (manager[i].id == _id)
			return i;
	return -1;
}
//查找记录
void query()
{
	int i;
	//用id查找 
	if ((i = find()) != -1)
	{
		print(i);
	}
	else
		printf("没有这个职工,查询失败!\n");
}

//修改记录
void update()
{
	int i;
	if ((i = find()) != -1)
	{
		printf("输入修改的姓名：");
		scanf("%s", manager[i].name);
		printf("输入修改的基本工资：");
		scanf("%f", &manager[i].baseWage);
		printf("输入修改的岗位津贴：");
		scanf("%f", &manager[i].allowance);
		printf("输入修改的医疗保险：");
		scanf("%f", &manager[i].insurance);
		printf("修改完成！\n\n");
	}
	else
		printf("没有这个职工,修改失败!\n");
}

//按姓名排序
void sortByName()
{
	int i, j;
	//冒泡排序
	for(i = 0;i < count - 1;++i)
		for(j = 0;j < count - 1 -i;++j)
			if (strcmp(manager[j].name, manager[j + 1].name) > 0)
			{
				Emp temp = manager[j];
				manager[j] = manager[j + 1];
				manager[j + 1] = temp;
			}
	printf("排序完成,请继续查看！\n");
}

//保存信息
void save()
{
	FILE *fp;
	if ((fp = fopen("info.dat", "wb")) == NULL)
	{
		printf("创建失败！\n");
		return;
	}
	fwrite(manager, sizeof(Emp), count, fp);
	fclose(fp);
}
//菜单
void menu()
{
	int choice;
	while (1)
	{
		system("cls");
		printf("\t\t职工管理\n");
		printf("\t【0】退出\n");
		printf("\t【1】输入记录\n");
		printf("\t【2】显示记录\n");
		printf("\t【3】修改记录\n");
		printf("\t【4】查找记录\n");
		printf("\t【5】姓名排序\n");
		printf("选择功能：(0 - 5)：");
		scanf("%d", &choice);
		switch (choice)
		{
		case 0:save();
			return;
		case 1:input();
			break;
		case 2:show();
			break;
		case 3:update();
			break;
		case 4:query();
			break;
		case 5:sortByName();
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

