#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Employee {
	char name[20];			//����
	int id;							//id
	float baseWage;		//��������
	float allowance;		//��λ����
	float insurance;		//ҽ�Ʊ���
}Emp;

int count = 0;				//��¼����
Emp manager[1024];//��Ϣ��������
 
//��Ϣ¼��
void input()
{
	int choice;
	while (1)//ѭ������,ֱ���û�ѡ���˳�
	{
		printf("����������");
		scanf("%s", manager[count].name);
		printf("����id��");
		scanf("%d", &manager[count].id);
		printf("����������ʣ�");
		scanf("%f", &manager[count].baseWage);
		printf("�����λ������");
		scanf("%f", &manager[count].allowance);
		printf("����ҽ�Ʊ��գ�");
		scanf("%f", &manager[count].insurance);
		count++;
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
	printf("��λ������%.2f\n", manager[i].allowance);
	printf("ҽ�Ʊ��գ�%.2f\n", manager[i].insurance);
}
//��ʾ��¼
void show()
{
	int i;
	//ѭ����ӡ������Ϣ
	for (i = 0; i < count; ++i)
		print(i);
}
//����id���޸ĺͲ�ѯ��Ҫ�ã������ó���
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
//���Ҽ�¼
void query()
{
	int i;
	//��id���� 
	if ((i = find()) != -1)
	{
		print(i);
	}
	else
		printf("û�����ְ��,��ѯʧ��!\n");
}

//�޸ļ�¼
void update()
{
	int i;
	if ((i = find()) != -1)
	{
		printf("�����޸ĵ�������");
		scanf("%s", manager[i].name);
		printf("�����޸ĵĻ������ʣ�");
		scanf("%f", &manager[i].baseWage);
		printf("�����޸ĵĸ�λ������");
		scanf("%f", &manager[i].allowance);
		printf("�����޸ĵ�ҽ�Ʊ��գ�");
		scanf("%f", &manager[i].insurance);
		printf("�޸���ɣ�\n\n");
	}
	else
		printf("û�����ְ��,�޸�ʧ��!\n");
}

//����������
void sortByName()
{
	int i, j;
	//ð������
	for(i = 0;i < count - 1;++i)
		for(j = 0;j < count - 1 -i;++j)
			if (strcmp(manager[j].name, manager[j + 1].name) > 0)
			{
				Emp temp = manager[j];
				manager[j] = manager[j + 1];
				manager[j + 1] = temp;
			}
	printf("�������,������鿴��\n");
}

//������Ϣ
void save()
{
	FILE *fp;
	if ((fp = fopen("info.dat", "wb")) == NULL)
	{
		printf("����ʧ�ܣ�\n");
		return;
	}
	fwrite(manager, sizeof(Emp), count, fp);
	fclose(fp);
}
//�˵�
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
		printf("\t��5����������\n");
		printf("ѡ���ܣ�(0 - 5)��");
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

