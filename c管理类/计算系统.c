#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int a, b;
int N = 1;
double highRecord[4] = {0};

void load();
void save(const char* fileName, const char* openMode, double operand);
//���������
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
	default:printf("�������");
		break;
	}
}
//ѡ��Χ�˵�
void randMenu()
{
	printf("��1��10����\n");
	printf("��2��20����\n");
	printf("��3��50����\n");
	printf("��4��100����\n");
	scanf("%d", &N);
	createRand(N);
}

//����
void operation(int n,char c)
{
	int  count = 0, correct = 0, answer;
	char ch;
	while (1)
	{
		createRand(N);
		if (n == 4)
			printf("����ȡ����\n");
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
		printf("�Ƿ����?(y or n)��");
		getchar();
		scanf("%c", &ch);
		if (ch == 'n' || ch == 'N')
			break;
	}
	double record = (float)correct / count * 100;
	printf("������ϰ��׼ȷ��Ϊ��%.2f%%\n", record);
	load();
	if (record > highRecord[n - 1])
	{
		highRecord[n - 1] = record;
		if (n == 1)
			printf("�ӷ���ȡ������߷�\n");
		if (n == 2)
			printf("��������������ˣ�������\n");
		if (n == 3)
			printf("�˷�ѧ�ĺܺ�Ŷ��\n");
		if (n == 4)
			printf("�����ܵеĳ�����\n");
	}
	save("score.txt", "a",record);
	save("high.txt", "w",0);
}

//��ȡ��¼
void load()
{
	FILE  *fp;
	if ((fp = fopen("high", "r")) == NULL)
		return;
	fscanf(fp, "%lf%lf%lf%lf", &highRecord[0], &highRecord[1], &highRecord[2], &highRecord[3]);
	fclose(fp);
}
//д���¼
void save(const char* fileName,const char* openMode,double operand)
{
	FILE *fp;
	if ((fp = fopen(fileName, openMode)) == NULL)
	{
		printf("�ļ���ʧ�ܣ�\n");
		return;
	}
	if (fileName == "score.txt")
		fprintf(fp, "%.2lf\n", operand);
	else
		fprintf(fp, "%.2lf\t%.2lf\t%.2lf\t%.2lf\n", highRecord[0], highRecord[1], highRecord[2], highRecord[3]);
	fclose(fp);
}
//�Ӳ˵�
void childMenu()
{
	while (1)
	{
		system("cls");
		int choice;
		printf("��0�������ϼ��˵�\n");
		printf("��1���ӷ���ϰ\n");
		printf("��2��������ϰ\n");
		printf("��3���˷���ϰ\n");
		printf("��4��������ϰ\n");
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
		default:printf("�������\n");
			break;
		}
		system("pause");
	}
}
//���˵�
void menu()
{
	int choice;
	while (1)
	{
		system("cls");
		printf("----Сѧ��������ϰϵͳ----\n");
		printf("��0���˳�ϵͳ\n");
		printf("��1��������ϰ\n");
		printf("��2��ѡ��Χ\n");
		scanf("%d", &choice);
		if (choice == 0)
			break;
		else if (choice == 1)
			childMenu();
		else if (choice == 2)
			randMenu();
		else
			printf("�������\n");
	}
}

int main()
{
	menu();
	return 0;
}
