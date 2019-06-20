#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

#define N 20
typedef struct Player
{
	int num;		//���
	char name[N];	//����
	float score[10];//10λ��ί���
}Play;

typedef struct Manage
{
	Play p;
	float avgScore;
	float sumScore;
}Man;


int count = 0;		//ѡ�ָ���
Man manage[1024];	//��������

//����ѡ�ֻ�����Ϣ
void input()
{
	int choice;
	while (1)
	{
		printf("����ѡ��%d��������", count + 1);
		scanf("%s", manage[count].p.name);
		printf("����ѡ��%d�ı�ţ�", count + 1);
		scanf("%d", &manage[count].p.num);
		printf("�Ƿ������(0:��  1:��)��");
		count++;
		scanf("%d", &choice);
		if (choice == 0)
			break;
	}
}

//��ί���
void mark()
{
	int i,j;
	float max = -1, min = 101;
	for (i = 0; i < count; ++i)
	{
		printf("ѡ��%d\n", i + 1);
		for (j = 0; j < 10; ++j)
		{
			printf("������ί%d�ķ�����", j + 1);
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

//�ɼ�����(��ƽ����)
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
	printf("������ɣ�\n");
}

//���ݲ�ѯ(�����)
void query()
{
	int _num, tag = 0 , i,j;
	printf("�����ţ�");
	scanf("%d", &_num);
	for (i = 0; i < count; ++i)
	{
		if (manage[i].p.num == _num)
		{
			tag = 1;
			printf("��ţ�%d\n", manage[i].p.num);
			printf("������%s\n", manage[i].p.name);
			printf("ƽ���֣�%.2f\n", manage[i].avgScore);
			printf("�ܷ֣�%.2f\n", manage[i].sumScore);
			printf("ʮ����ί�ķ���\n");
			for (j = 0; j < 10; ++j)
			{
				printf("%.2f\t", manage[i].p.score[j]);
				if (j == 4)
					printf("\n");
			}
		}
	}
	if (!tag)
		printf("û���ҵ����ˣ�\n");
}

//׷������
void append()
{
	input();
}

//д�������ļ�
void write()
{
	FILE *fp;
	if ((fp = fopen("info.dat", "wb")) == NULL)
	{
		printf("�ļ�д��ʧ�ܣ�\n");
		return;
	}

	fwrite(manage, sizeof(Man), count, fp);
	fclose(fp);
}

void menu()
{
	int choice,i;
	const char title[7][1024] = {
		"����ѡ������","��ί���",
		"�ɼ�����(��ƽ����)",
		"���ݲ�ѯ","׷������",
		"д�������ļ�","�˳�"
	};
	
	while (1)
	{
		system("cls");
		printf("*****���ֱ���ϵͳ*****\n");
		for (i = 0; i < 7; ++i)
			printf("\t[%d]%s\n", i + 1, title[i]);
		printf("����ѡ��(1 - 7)��");
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
