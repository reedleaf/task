/*��Ŀ6��ѧ��ͨѶ¼����ϵͳ
�����Ҫ��ʵ�ֱ���ͬѧ��ͨѶ¼����ϵͳ���������Ϣ������
ѧ�š��������ֻ���QQ��EMAIL����ͥסַ����ͥ��ϵ�˺ͼ�ͥ�绰�ȣ�
�������������Ϣ����ӡ����ҡ�ɾ����������ʾ���޸ĺͱ���ȡ�
ϵͳ���ܣ�
a.��Ϣ¼�룺�����ͨѶ��¼��
b.��Ϣ��ʾ�������е�ͬѧͨѶ��Ϣ��˳����ʾ������ֻ��ʾ���е�һ�����У�
c.��Ϣ�޸ģ����Ѿ�������Ϣ�����޸ģ�ѧ�����������޸ģ���
d.��Ϣɾ����ɾ��ĳ����¼��
e.��ѯ���ɰ���ѧ�Ż���������ѯ��Ϣ
f.��Ϣ���棺��ͨѶ��Ϣ���浽�ļ���
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//ͨѶ¼����������󳤶�
#define MAXSIZE 20
//ѧ�š��������ֻ���QQ��EMAIL����ͥסַ����ͥ��ϵ�˺ͼ�ͥ�绰�ȣ�
//������Ϣ�ṹ��
typedef struct  Information {			
	char name[20];				//����
	char num[20];				//ѧ��
	char phone_number[20];		//�ֻ�����
	char QQ[20];				//QQ 
	char E_mail[20];			//E-mail��ַ
	char home_address[20];		//��ͥסַ
	char home_poerson[20];		//��ϵ�� 
	char home_phone[20];		//��ͥ�绰 
}Info;

int count=0;
Info management[MAXSIZE];

//����ѧ���Ƿ��ظ�
int ForDuplicates(char _num[])
{
	int i;
	for (i = 0; i < count; ++i)
	{
		//���ҵ���ȵ�ѧ�ţ�����1
		if (strcmp(management[i].num, _num) == 0)
			return i;
	}
	return -1;
}
//a.��Ϣ¼�룺�����ͨѶ��¼��
//����һ��ͨѶ¼
void addAddressBook()
{
	while (count <= MAXSIZE)
	{
		int n;

		printf("����������");
		scanf("%s",management[count].name);

		printf("����ѧ�ţ�");
		scanf("%s", management[count].num);
		if (ForDuplicates(management[count].num)!=-1)
		{
			printf("ѧ���ظ���¼��ʧ�ܣ�\n");
			break;
		}

		printf("����绰���룺");
		scanf("%s", management[count].phone_number);
	
		printf("����QQ��");
		scanf("%s", management[count].QQ);
		
		printf("�����ͥסַ��");
		scanf("%s", management[count].home_address);

		printf("����E-mail��");
		scanf("%s", management[count].E_mail);
		
		printf("�����ͥ��ϵ�ˣ�");
		scanf("%s",management[count].home_poerson);
		
		printf("�����ͥ�绰��");
		scanf("%s",management[count].home_phone);

		count++;
		printf("�Ƿ����(0:�� 1:��)��");
		scanf("%d", &n);
		if (!n)
			break;
	}
}
//ɾ��һ��ͨѶ¼(����ѧ�ţ�ѧ����Ψһ��)
void deleteAddressBook() 
{
	int i,j;
	char _num[20];
	
	printf("����Ҫɾ����ѧ����ѧ�ţ�");
	scanf("%s", _num);
	//����ѧ��
	i = ForDuplicates(_num);

	if (i == -1)
	{
		printf("û�����ѧ������Ϣ��ɾ��ʧ�ܣ�\n");
		system("pause");
		return;
	}

	for (j = i; j < count; ++j)
	{
		//��ǰ��ɾ��
		management[j] = management[j + 1];
	}
	count--;

	printf("ɾ���ɹ���\n");
}
//��ӡһ����¼
void print(int i)
{
	printf("------------------------\n");
	printf("������%s\n", management[i].name);
	printf("ѧ�ţ�%s\n", management[i].num);
	printf("�绰���룺%s\n", management[i].phone_number);
	printf("QQ��%s\n", management[i].QQ);
	printf("��ͥסַ��%s\n", management[i].home_address);
	printf("E-mail��ַ��%s\n", management[i].E_mail);
	printf("��ͥ��ϵ�ˣ�%s\n", management[i].home_poerson);
	printf("��ͥ�绰��%s\n", management[i].home_phone);
}
void nameSort();
//��ʾ���������ͨѶ¼
void printAddressBook()
{
	int i;
	//������ 
	nameSort();
	for (i = 0; i < count; ++i)
	{
		print(i);
	}
}
//�޸�ĳ��ͨѶ¼(����ѧ�ţ�ѧ����Ψһ��)
void updateAddressBook()
{
	int i;
	char _num[20];

	printf("����Ҫ�޸�ѧ����ѧ�ţ�");
	scanf("%s", _num);
	//ͬ��,���治˵��
	i = ForDuplicates(_num);
	
	if (i == -1)
	{
		printf("û�����ѧ�����޸�ʧ�ܣ�\n");
		system("pause");
		return;
	}
	printf("�����޸ĵ�QQ��");
	scanf("%s", management[count].QQ);
	printf("�����޸ĵ��ֻ����룺");
	scanf("%s", management[count].phone_number);
	printf("�����޸ĵļ�ͥסַ��");
	scanf("%s", management[count].home_address);
	printf("�����޸ĵļ�ͥ��ϵ�ˣ�");
	scanf("%s", management[count].home_poerson);
	printf("�����޸ĵ�E-mail��");
	scanf("%s", management[count].E_mail);
	printf("�����޸ĵļ�ͥ�绰��");
	scanf("%s", management[count].home_phone);


	printf("�޸���ɣ�\n");
}
//������������(ð������)
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
//����������ѯ��Ϣ 
void nameFindInfo()
{
	int i;
	char _name[20];

	printf("�����ѯ��ѧ����������");
	scanf("%s", _name);

	for (i = 0; i < count; ++i)
	{
		//strcmp�ж��ַ����Ƿ����
		if (!(strcmp(management[i].name, _name)))
			print(i); 
	}
}
//ѧ�Ų�ѯ��Ϣ
void numFindInfo()
{
	int i;
	char _num[20];
	
	printf("�����ѯ��ѧ����ѧ�ţ�");
	scanf("%s",_num);
	
	for (i = 0; i < count; ++i)
	{	//ͬ��
		if (!(strcmp(management[i].num, _num)))
			print(i); 
	}
}
//�ļ�д��
void save()
{
	char ch,ch_1;
	FILE *fp;

	if ((fp = fopen("AddressBook.dat", "wb")) == NULL)
	{
		printf("��ʧ�ܣ�\n");
		system("pause");
		exit(1);
	}
	//������Ϣ�����͵绰�������
	ch = count + '0';
	fputc(ch, fp);

	fwrite(management, sizeof(Info), count, fp);

	fclose(fp);
}
//�ļ���ȡ
void read()
{
	char ch;
	FILE *fp,*rp;
	//����һ�����ӵ��ļ�����ֹ��һ��ʹ��û���ļ����³���
	if ((rp = fopen("AddressBook.dat", "ab")) == NULL)
	{
		printf("��ʧ�ܣ�\n");
		system("pause");
		exit(1);
	}
	fclose(rp);

	if ((fp = fopen("AddressBook.dat", "rb")) == NULL)
	{
		printf("��ʧ�ܣ�\n");
		system("pause");
		exit(1);
	}
	//��ȡ��Ϣ����
	ch = fgetc(fp);
	count = ch - '0';

	if (count < 0)
		count = 0;

	fread(management, sizeof(Info), count, fp);

	fclose(fp);
}
//ѡ��˵�
void menu()
{
	while (1)
	{
		int n;
		system("cls");
		printf("\t\t\t<����ͨѶ¼>\n");
		printf("\t\t\t<0>�˳�ϵͳ\n");
		printf("\t\t\t<1>����һ��ͨѶ¼\n");
		printf("\t\t\t<2>ɾ��һ��ͨѶ¼\n");
		printf("\t\t\t<3>��ʾ����ͨѶ¼\n");
		printf("\t\t\t<4>�޸�ĳ��ͨѶ¼\n");
		printf("\t\t\t<5>��������ѯͨѶ¼\n");
		printf("\t\t\t<6>��ѧ�Ų�ѯͨѶ¼\n");
		printf("����ѡ��(1-6)��");
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

