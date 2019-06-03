/*题目6：学生通讯录管理系统
该设计要求实现本班同学的通讯录管理系统，保存的信息包括：
学号、姓名、手机、QQ、EMAIL、家庭住址、家庭联系人和家庭电话等，
具体操作包括信息的添加、查找、删除、排序、显示、修改和保存等。
系统功能：
a.信息录入：即添加通讯记录。
b.信息显示：将所有的同学通讯信息按顺序显示（可以只显示其中的一部分列）
c.信息修改：对已经输入信息进行修改（学号姓名不能修改）。
d.信息删除：删除某个记录。
e.查询：可按照学号或者姓名查询信息
f.信息保存：将通讯信息保存到文件。
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//通讯录管理数组最大长度
#define MAXSIZE 20
//学号、姓名、手机、QQ、EMAIL、家庭住址、家庭联系人和家庭电话等，
//基本信息结构体
typedef struct  Information {			
	char name[20];				//姓名
	char num[20];				//学号
	char phone_number[20];		//手机号码
	char QQ[20];				//QQ 
	char E_mail[20];			//E-mail地址
	char home_address[20];		//家庭住址
	char home_poerson[20];		//联系人 
	char home_phone[20];		//家庭电话 
}Info;

int count=0;
Info management[MAXSIZE];

//查找学号是否重复
int ForDuplicates(char _num[])
{
	int i;
	for (i = 0; i < count; ++i)
	{
		//查找到相等的学号，返回1
		if (strcmp(management[i].num, _num) == 0)
			return i;
	}
	return -1;
}
//a.信息录入：即添加通讯记录。
//增加一条通讯录
void addAddressBook()
{
	while (count <= MAXSIZE)
	{
		int n;

		printf("输入姓名：");
		scanf("%s",management[count].name);

		printf("输入学号：");
		scanf("%s", management[count].num);
		if (ForDuplicates(management[count].num)!=-1)
		{
			printf("学号重复！录入失败！\n");
			break;
		}

		printf("输入电话号码：");
		scanf("%s", management[count].phone_number);
	
		printf("输入QQ：");
		scanf("%s", management[count].QQ);
		
		printf("输入家庭住址：");
		scanf("%s", management[count].home_address);

		printf("输入E-mail：");
		scanf("%s", management[count].E_mail);
		
		printf("输入家庭联系人：");
		scanf("%s",management[count].home_poerson);
		
		printf("输入家庭电话：");
		scanf("%s",management[count].home_phone);

		count++;
		printf("是否继续(0:否 1:是)：");
		scanf("%d", &n);
		if (!n)
			break;
	}
}
//删除一条通讯录(根据学号，学号是唯一的)
void deleteAddressBook() 
{
	int i,j;
	char _num[20];
	
	printf("输入要删除的学生的学号：");
	scanf("%s", _num);
	//查找学号
	i = ForDuplicates(_num);

	if (i == -1)
	{
		printf("没有这个学生的信息，删除失败！\n");
		system("pause");
		return;
	}

	for (j = i; j < count; ++j)
	{
		//往前移删除
		management[j] = management[j + 1];
	}
	count--;

	printf("删除成功！\n");
}
//打印一条记录
void print(int i)
{
	printf("------------------------\n");
	printf("姓名：%s\n", management[i].name);
	printf("学号：%s\n", management[i].num);
	printf("电话号码：%s\n", management[i].phone_number);
	printf("QQ：%s\n", management[i].QQ);
	printf("家庭住址：%s\n", management[i].home_address);
	printf("E-mail地址：%s\n", management[i].E_mail);
	printf("家庭联系人：%s\n", management[i].home_poerson);
	printf("家庭电话：%s\n", management[i].home_phone);
}
void nameSort();
//显示保存的所有通讯录
void printAddressBook()
{
	int i;
	//先排序 
	nameSort();
	for (i = 0; i < count; ++i)
	{
		print(i);
	}
}
//修改某条通讯录(根据学号，学号是唯一的)
void updateAddressBook()
{
	int i;
	char _num[20];

	printf("输入要修改学生的学号：");
	scanf("%s", _num);
	//同上,下面不说了
	i = ForDuplicates(_num);
	
	if (i == -1)
	{
		printf("没有这个学生，修改失败！\n");
		system("pause");
		return;
	}
	printf("输入修改的QQ：");
	scanf("%s", management[count].QQ);
	printf("输入修改的手机号码：");
	scanf("%s", management[count].phone_number);
	printf("输入修改的家庭住址：");
	scanf("%s", management[count].home_address);
	printf("输入修改的家庭联系人：");
	scanf("%s", management[count].home_poerson);
	printf("输入修改的E-mail：");
	scanf("%s", management[count].E_mail);
	printf("输入修改的家庭电话：");
	scanf("%s", management[count].home_phone);


	printf("修改完成！\n");
}
//根据姓名排序(冒泡排序)
void nameSort()
{
	int i, j;
	Info temp;

	for(i=0;i<count-1;++i)
		for (j = 0; j < count - 1 - i; ++j)
		{
			if (strcmp(management[j].name, management[j + 1].name) > 0)
			{
				temp = management[j];
				management[j] = management[j + 1];
				management[j + 1] = temp;
			}
		}
}
//根据姓名查询信息 
void nameFindInfo()
{
	int i;
	char _name[20];

	printf("输入查询的学生的姓名：");
	scanf("%s", _name);

	for (i = 0; i < count; ++i)
	{
		//strcmp判断字符串是否相等
		if (!(strcmp(management[i].name, _name)))
			print(i); 
	}
}
//学号查询信息
void numFindInfo()
{
	int i;
	char _num[20];
	
	printf("输入查询的学生的学号：");
	scanf("%s",_num);
	
	for (i = 0; i < count; ++i)
	{	//同上
		if (!(strcmp(management[i].num, _num)))
			print(i); 
	}
}
//文件写入
void save()
{
	char ch,ch_1;
	FILE *fp;

	if ((fp = fopen("AddressBook.dat", "wb")) == NULL)
	{
		printf("打开失败！\n");
		system("pause");
		exit(1);
	}
	//存入信息个数和电话号码个数
	ch = count + '0';
	fputc(ch, fp);

	fwrite(management, sizeof(Info), count, fp);

	fclose(fp);
}
//文件读取
void read()
{
	char ch;
	FILE *fp,*rp;
	//创建一个附加的文件，防止第一次使用没有文件导致出错
	if ((rp = fopen("AddressBook.dat", "ab")) == NULL)
	{
		printf("打开失败！\n");
		system("pause");
		exit(1);
	}
	fclose(rp);

	if ((fp = fopen("AddressBook.dat", "rb")) == NULL)
	{
		printf("打开失败！\n");
		system("pause");
		exit(1);
	}
	//读取信息个数
	ch = fgetc(fp);
	count = ch - '0';

	if (count < 0)
		count = 0;

	fread(management, sizeof(Info), count, fp);

	fclose(fp);
}
//选择菜单
void menu()
{
	while (1)
	{
		int n;
		system("cls");
		printf("\t\t\t<个人通讯录>\n");
		printf("\t\t\t<0>退出系统\n");
		printf("\t\t\t<1>增加一条通讯录\n");
		printf("\t\t\t<2>删除一条通讯录\n");
		printf("\t\t\t<3>显示所有通讯录\n");
		printf("\t\t\t<4>修改某条通讯录\n");
		printf("\t\t\t<5>按姓名查询通讯录\n");
		printf("\t\t\t<6>按学号查询通讯录\n");
		printf("输入选择(1-6)：");
		scanf("%d", &n);

		switch (n)
		{
		case 0:return;
			break;
		case 1:addAddressBook();
			break;
		case 2:deleteAddressBook();
			break;
		case 3:printAddressBook();
			break;
		case 4:updateAddressBook();
			break;
		case 5:nameFindInfo();
			break;
		case 6:numFindInfo();
			break;
		}
		system("pause");
	}
}
int main()
{
	read();
	menu();
	save();
	system("pause");
	return 0;
}

