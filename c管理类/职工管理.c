
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 20

typedef struct Employee {
	char name[N];		//姓名
	int id;				//id
	float baseWage;		//基本工资
	float positionWage;	//职务工资
	float allowance;	//岗位津贴
	float insurance;	//医疗保险
	float MPF;			//公积金 
	float sum;			//总工资 
	float avg;			//平均工资 
}Emp;

int count = 0;
Emp manager[1024];
float SUM[5];

//输入记录
void input()
{
	int choice;
	while (1)
	{
		printf("输入姓名：");
		scanf("%s", manager[count].name);
		printf("输入id：");
		scanf("%d", &manager[count].id);
		printf("输入基本工资：");
		scanf("%f", &manager[count].baseWage);
		printf("输入职务工资：");
		scanf("%f", &manager[count].positionWage);
		printf("输入岗位津贴：");
		scanf("%f", &manager[count].allowance);
		printf("输入医疗保险：");
		scanf("%f", &manager[count].insurance);
		printf("输入公积金：");
		scanf("%f", &manager[count].MPF);
		manager[count].sum = 0;
		manager[count++].avg = 0;
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
	printf("职务工资：%.2f\n", manager[i].positionWage);
	printf("岗位津贴：%.2f\n", manager[i].allowance);
	printf("医疗保险：%.2f\n", manager[i].insurance);
	printf("公积金：%.2f\n", manager[i].MPF);
}
//显示记录
void show()
{
	int i;
	for (i = 0; i < count; ++i)
		print(i);
}

//查找id
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
//修改记录
void update()
{
	int i;
	if ((i = find()) != -1)
	{
		printf("修改前的记录：\n\n");
		print(i);
		printf("输入修改的姓名：");
		scanf("%s", manager[i].name);
		printf("输入修改的基本工资：");
		scanf("%f", &manager[i].baseWage);
		printf("输入修改的职务工资：");
		scanf("%f", &manager[i].positionWage);
		printf("输入修改的岗位津贴：");
		scanf("%f", &manager[i].allowance);
		printf("输入修改的医疗保险：");
		scanf("%f", &manager[i].insurance);
		printf("输入修改的公积金：");
		scanf("%f", &manager[i].MPF);
		printf("修改完成！\n\n");
		printf("修改后的记录：\n\n");
		print(i);
	}
	else
		printf("没有这个职工,修改失败!\n");
}
//查找记录
void query()
{
	int i;
	if ((i = find()) != -1)
	{
		print(i);
	}
	else
		printf("没有这个职工,查询失败!\n");
}
//删除记录
void deleteInfo()
{
	int i, j;
	if ((i = find()) != -1)
	{
		for (j = i; j < count; ++j)
			manager[j] = manager[j + 1];
		printf("删除成功！\n");
		count--;
	}
	else
		printf("没有这个职工,删除失败!\n");
}
//(A)计算各项工资平均工资及总工资, 
void avgAndSum(int n)
{
	int i;
	for (i = 0; i < count; ++i)
	{
		manager[i].sum += manager[i].baseWage + manager[i].allowance + manager[i].insurance
			+ manager[i].positionWage + manager[i].MPF;
		manager[i].avg = manager[i].sum / 5;
		if(n == 1)
			printf("职工%s的总工资为：%.2f\t平均工资为：%.2f\n", manager[i].name, manager[i].sum, manager[i].avg);
	}
}
//(B)统计符合指定条件(如职工工资前三项之和在3000元以上、3000~2000元、2000~1000元) 以内的工资职工人数及占总职工人数的百分比。
void firstThreeSum()
{
	int a = 0, b = 0, c = 0, i;
	for (i = 0; i < count; ++i)
	{
		if (manager[i].sum > 3000)
			a++;
		else if (manager[i].sum > 2000)
			b++;
		else if (manager[i].sum > 1000)
			c++;
	}
	printf("工资在3000以上的有%d个,2000-3000的有%d个,1000-2000的有%d个\n", a, b, c);
}
//(C)按字符表格形式打印全部职工工资信息表及平均工资(包括各项总的平均工资)。
void printTable(int n)
{
	int i;
	avgAndSum(0);
	if(n == 1)
		printf("ID\t姓名\t基本工资\t职务工资\t津贴\t医疗保险\t公积金\n");
	for (i = 0; i < count; ++i)
	{
		if(n == 1)
		{
			printf("%d\t%s\t%.2f\t\t%.2f\t\t%.2f\t%.2f\t\t%.2f\n\n",
			manager[i].id, manager[i].name, manager[i].baseWage, manager[i].positionWage,
			manager[i].allowance, manager[i].insurance, manager[i].MPF);
		}
		SUM[0] += manager[i].baseWage;
		SUM[1] += manager[i].positionWage;
		SUM[2] += manager[i].allowance;
		SUM[3] += manager[i].insurance;
		SUM[4] += manager[i].MPF;
	}
	if(n == 1)
		printf("各项总平均工资：%.2f\t%.2f\t%.2f\t%.2f\t%.2f\n", SUM[0] / count, SUM[1] / count, SUM[2] / count, SUM[3] / count, SUM[4] / count);
}

//统计记录
void countInfo()
{
	int choice;
	while (1)
	{
		system("cls");
		printf("【1】计算平均工资和总工资\n");
		printf("【2】统计总工资阶段人数\n");
		printf("【3】打印信息表\n");
		printf("【4】返回上一层\n");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:avgAndSum(1);
			break;
		case 2:firstThreeSum();
			break;
		case 3:printTable(1);
			break;
		case 4:return;
		default:printf("输入错误！\n");
			break;
		}
		system("pause");
	}
}
//保存文件
void save()
{
	int i;
	FILE *fp;
	printTable(0);
	if ((fp = fopen("employee.txt", "w")) == NULL)
	{
		printf("文件创建失败！\n");
		return;
	}
	fprintf(fp, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", "ID号", "姓名", "基本工资", "职务工资", "津贴", "医疗保险", "公积金", "总工资");
	for (i = 0; i < count; ++i)
	{
		fprintf(fp, "%d\t%s\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t\n",
			manager[i].id, manager[i].name, manager[i].baseWage, manager[i].positionWage,
			manager[i].allowance, manager[i].insurance, manager[i].MPF, manager[i].sum);
	}
	fprintf(fp,"各项总平均工资：%.2f\t%.2f\t%.2f\t%.2f\t%.2f\n", SUM[0] / count, SUM[1] / count, SUM[2] / count, SUM[3] / count, SUM[4] / count);
	fclose(fp);
	printf("保存成功！\n");
}

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
		printf("\t【5】删除记录\n");
		printf("\t【6】统计记录\n");
		printf("\t【7】保存记录\n");
		printf("选择功能：(0 - 7)：");
		scanf("%d", &choice);
		switch (choice)
		{
		case 0:return;
			break;
		case 1:input();
			break;
		case 2:show();
			break;
		case 3:update();
			break;
		case 4:query();
			break;
		case 5:deleteInfo();
			break;
		case 6:countInfo();
			break;
		case 7:save();
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
