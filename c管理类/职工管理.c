
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 20

typedef struct Employee {
	char name[N];		//����
	int id;				//id
	float baseWage;		//��������
	float positionWage;	//ְ����
	float allowance;	//��λ����
	float insurance;	//ҽ�Ʊ���
	float MPF;			//������ 
	float sum;			//�ܹ��� 
	float avg;			//ƽ������ 
}Emp;

int count = 0;
Emp manager[1024];
float SUM[5];

//�����¼
void input()
{
	int choice;
	while (1)
	{
		printf("����������");
		scanf("%s", manager[count].name);
		printf("����id��");
		scanf("%d", &manager[count].id);
		printf("����������ʣ�");
		scanf("%f", &manager[count].baseWage);
		printf("����ְ���ʣ�");
		scanf("%f", &manager[count].positionWage);
		printf("�����λ������");
		scanf("%f", &manager[count].allowance);
		printf("����ҽ�Ʊ��գ�");
		scanf("%f", &manager[count].insurance);
		printf("���빫����");
		scanf("%f", &manager[count].MPF);
		manager[count].sum = 0;
		manager[count++].avg = 0;
		printf("�Ƿ������(0:�� 1:��)��");
		scanf("%d", &choice);
		if (choice == 0)
			break;
	}
}
//��ӡ
void print(int i)
{
	printf("***********Ա��%d************\n", i + 1);
	printf("������%s\n", manager[i].name);
	printf("ID��%d\n", manager[i].id);
	printf("�������ʣ�%.2f\n", manager[i].baseWage);
	printf("ְ���ʣ�%.2f\n", manager[i].positionWage);
	printf("��λ������%.2f\n", manager[i].allowance);
	printf("ҽ�Ʊ��գ�%.2f\n", manager[i].insurance);
	printf("������%.2f\n", manager[i].MPF);
}
//��ʾ��¼
void show()
{
	int i;
	for (i = 0; i < count; ++i)
		print(i);
}

//����id
int find()
{
	int _id, i;
	printf("����ְ����id��");
	scanf("%d", &_id);
	for (i = 0; i < count; ++i)
		if (manager[i].id == _id)
			return i;
	return -1;
}
//�޸ļ�¼
void update()
{
	int i;
	if ((i = find()) != -1)
	{
		printf("�޸�ǰ�ļ�¼��\n\n");
		print(i);
		printf("�����޸ĵ�������");
		scanf("%s", manager[i].name);
		printf("�����޸ĵĻ������ʣ�");
		scanf("%f", &manager[i].baseWage);
		printf("�����޸ĵ�ְ���ʣ�");
		scanf("%f", &manager[i].positionWage);
		printf("�����޸ĵĸ�λ������");
		scanf("%f", &manager[i].allowance);
		printf("�����޸ĵ�ҽ�Ʊ��գ�");
		scanf("%f", &manager[i].insurance);
		printf("�����޸ĵĹ�����");
		scanf("%f", &manager[i].MPF);
		printf("�޸���ɣ�\n\n");
		printf("�޸ĺ�ļ�¼��\n\n");
		print(i);
	}
	else
		printf("û�����ְ��,�޸�ʧ��!\n");
}
//���Ҽ�¼
void query()
{
	int i;
	if ((i = find()) != -1)
	{
		print(i);
	}
	else
		printf("û�����ְ��,��ѯʧ��!\n");
}
//ɾ����¼
void deleteInfo()
{
	int i, j;
	if ((i = find()) != -1)
	{
		for (j = i; j < count; ++j)
			manager[j] = manager[j + 1];
		printf("ɾ���ɹ���\n");
		count--;
	}
	else
		printf("û�����ְ��,ɾ��ʧ��!\n");
}
//(A)��������ƽ�����ʼ��ܹ���, 
void avgAndSum(int n)
{
	int i;
	for (i = 0; i < count; ++i)
	{
		manager[i].sum += manager[i].baseWage + manager[i].allowance + manager[i].insurance
			+ manager[i].positionWage + manager[i].MPF;
		manager[i].avg = manager[i].sum / 5;
		if(n == 1)
			printf("ְ��%s���ܹ���Ϊ��%.2f\tƽ������Ϊ��%.2f\n", manager[i].name, manager[i].sum, manager[i].avg);
	}
}
//(B)ͳ�Ʒ���ָ������(��ְ������ǰ����֮����3000Ԫ���ϡ�3000~2000Ԫ��2000~1000Ԫ) ���ڵĹ���ְ��������ռ��ְ�������İٷֱȡ�
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
	printf("������3000���ϵ���%d��,2000-3000����%d��,1000-2000����%d��\n", a, b, c);
}
//(C)���ַ������ʽ��ӡȫ��ְ��������Ϣ��ƽ������(���������ܵ�ƽ������)��
void printTable(int n)
{
	int i;
	avgAndSum(0);
	if(n == 1)
		printf("ID\t����\t��������\tְ����\t����\tҽ�Ʊ���\t������\n");
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
		printf("������ƽ�����ʣ�%.2f\t%.2f\t%.2f\t%.2f\t%.2f\n", SUM[0] / count, SUM[1] / count, SUM[2] / count, SUM[3] / count, SUM[4] / count);
}

//ͳ�Ƽ�¼
void countInfo()
{
	int choice;
	while (1)
	{
		system("cls");
		printf("��1������ƽ�����ʺ��ܹ���\n");
		printf("��2��ͳ���ܹ��ʽ׶�����\n");
		printf("��3����ӡ��Ϣ��\n");
		printf("��4��������һ��\n");
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
		default:printf("�������\n");
			break;
		}
		system("pause");
	}
}
//�����ļ�
void save()
{
	int i;
	FILE *fp;
	printTable(0);
	if ((fp = fopen("employee.txt", "w")) == NULL)
	{
		printf("�ļ�����ʧ�ܣ�\n");
		return;
	}
	fprintf(fp, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", "ID��", "����", "��������", "ְ����", "����", "ҽ�Ʊ���", "������", "�ܹ���");
	for (i = 0; i < count; ++i)
	{
		fprintf(fp, "%d\t%s\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t\n",
			manager[i].id, manager[i].name, manager[i].baseWage, manager[i].positionWage,
			manager[i].allowance, manager[i].insurance, manager[i].MPF, manager[i].sum);
	}
	fprintf(fp,"������ƽ�����ʣ�%.2f\t%.2f\t%.2f\t%.2f\t%.2f\n", SUM[0] / count, SUM[1] / count, SUM[2] / count, SUM[3] / count, SUM[4] / count);
	fclose(fp);
	printf("����ɹ���\n");
}

void menu()
{
	int choice;
	while (1)
	{
		system("cls");
		printf("\t\tְ������\n");
		printf("\t��0���˳�\n");
		printf("\t��1�������¼\n");
		printf("\t��2����ʾ��¼\n");
		printf("\t��3���޸ļ�¼\n");
		printf("\t��4�����Ҽ�¼\n");
		printf("\t��5��ɾ����¼\n");
		printf("\t��6��ͳ�Ƽ�¼\n");
		printf("\t��7�������¼\n");
		printf("ѡ���ܣ�(0 - 7)��");
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
		default:printf("�������\n");
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
