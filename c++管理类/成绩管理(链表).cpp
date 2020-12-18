/*################################
.      ԭ����д�����ſɿ���
.      ע����ϸ�����빤����
.      ˮƽһ���������׶���
.      ��ѭ�̲ģ��������١�
.          < ReedLeaf >
.        QQ : 1020273485
.  https://codefox.taobao.com
################################

.���ԡ�����C++
.���⡡����xxxxxxxxxxxxxxxxxxx
.��������������Ŀ����
.Ҫ�󡡣�������Ŀ����

ע��:
	��1�������ǰ��տͻ���������ϸҪ��ȥ��д��,�շ��ǰ��յ�ʱ��Ҫ������շѵġ����Ժ���Ҫ����ӹ��������ǲ�����,

	��2�� �õ�����󾡿���ԣ����������,�������ǹ������ܴ�,����һֱ��ʱ�����
			 �������û�һ���º��ҹ�������޸ĵ�����(��������һ���¶��ڸ����أ�)���������½�

	��3�����ǲ������̻��������,С�������������,������𲻹���Щ�ͻ���Ѵ�д�͸�����Ϊһ̸,��ͷ�����ǵõ��Ļ���һ��������
			 �����������Ķ���
*/
#define _CRT_SECURE_NO_WARNINGS
# include <iostream>
# include <fstream>
# include <string.h>
#include <conio.h>//��getch();
using namespace std;
int i;

//�k�k�k�k�k�k�k�k�k�kStudent��k�k�k�k�k�k�k�k�k�k�k
class Student
{
public:
	char name[20];
	char Id[20];
	int math;       //��ѧ
	int chemi;       //��ѧ
	int physics;       //���� 
	int internet;      //����
	int English;      //Ӣ�� 
	int sum;        //�ܷ�   
	int aver;      //ƽ����  
	Student * Next;
	void Input()
	{
		cout << "\t\t������ѧ����������";  cin >> name;
		cout << "\t\t������ѧ����ѧ�ţ�";  cin >> Id;
		cout << "\t\t��������ѧ�ɼ���";  cin >> math;
		cout << "\t\t�����뻯ѧ�ɼ���";  cin >> chemi;
		cout << "\t\t����������ɼ���";  cin >> physics;
		cout << "\t\t����������ɼ���";  cin >> internet;
		cout << "\t\t������Ӣ��ɼ���";  cin >> English;
	}
	void Calculate()
	{
		sum = math + chemi + physics + internet + English;
		aver = sum / 5;
	}
	void Show()
	{
		cout << "����:" << name << endl << "ѧ��:" << Id << endl << "��ѧ��" << math << endl
			<< "��ѧ��" << chemi << endl << "����" << physics << endl << "���磺" << internet << endl << "Ӣ�" << English << endl << "�ܳɼ�:" << sum << endl << "ƽ���֣�" << aver << endl << endl << endl;
	}
};

//�k�k�k�k�k�k�k�k�kStudentmassage��k�k�k�k�k�k�k�k�k�k�k�k
class Studentmassage
{
public:
	Studentmassage();
	~Studentmassage();
	void ShowMenu();
	void Find();
	void Save();
	void SaveRemove(Student*);
	void Recover();
	bool Read();
	void ModifyItem();
	void RemoveItem();
	void Swap(Student *, Student *);
	void Sort();
	void statistic();
	int ListCount();
	void Display()
	{
		for (Student * p = Head->Next; p != End; p = p->Next)
			p->Show();
		cout << "���������ַ�����������";
		_getch();
	}
	void AddItem()
	{
		End->Input();
		End->Calculate();
		End->Next = new Student;
		End = End->Next;
		cout << "����ɹ�!" << endl;
		cout << "���������ַ�����������";
		_getch();
	}
private:
	Student * Head, *End;
	ofstream out;
	ifstream infile;
	Student *FindItem(char * name)
	{
		for (Student * p = Head; p->Next != End; p = p->Next)//ƥ��ɹ��򷵻���һ��ָ�룬���ɹ��ͷ��ؿ�
			if (!strcmp(p->Next->name, name))return p;
		return NULL;
	}
	Student *FindID(char * Id)
	{
		for (Student * p = Head; p->Next != End; p = p->Next)//ƥ��ɹ��򷵻���һ��ָ�룬���ɹ��ͷ��ؿ�
			if (!strcmp(p->Next->Id, Id))return p;
		return NULL;
	}
};



//�k�k�k�k�k�k�k�k�k�k�k�k���캯���k�k�k�k�k�k�k�k�k�k�k�k
Studentmassage::Studentmassage()
{
	Head = new Student;
	Head->Next = new Student;
	End = Head->Next;
	if (!Read())
		cout << "����һ����ϵͳ����ѧ����Ϣ���������롣" << endl;
	else
		cout << "\t\t��ȡѧ����Ϣ�ɹ�!" << endl;
}

//�k�k�k�k�k�k�k�k�k�k�k�k���������k�k�k�k�k�k�k�k�k�k�k�k
Studentmassage::~Studentmassage()
{
	Save();
	for (Student * temp; Head->Next != End;)
	{
		temp = Head->Next;
		Head->Next = Head->Next->Next;
		delete temp;
	}
	delete Head, End;
}

//�k�k�k�k�k�k�k�k�k�k�k�k�˵��k�k�k�k�k�k�k�k�k�k�k�k
void Studentmassage::ShowMenu()
{
	cout << "********************************************************************************" << endl;
	cout << "��������������������  ��   ѧ �� �� �� �� �� ϵ  ͳ     ��  ��������������������" << endl;
	cout << "��������������������         ��������         �������������������" << endl;
	cout << "��������������������  ��          1.����ѧ���ɼ�        ��  �������������������" << endl;
	cout << "��������������������  ��          2.��ʾѧ���ɼ�        ��  �������������������" << endl;
	cout << "��������������������  ��          3.����ѧ���ɼ�        ��  �������������������" << endl;
	cout << "��������������������  ��          4.����ѧ���ɼ�        ��  �������������������" << endl;
	cout << "��������������������  ��          5.ɾ��ѧ���ɼ�        ��  �������������������" << endl;
	cout << "��������������������  ��          6.�޸�ѧ����Ϣ        ��  �������������������" << endl;
	cout << "��������������������  ��          7.ͳ��ѧ����Ϣ        ��  �������������������" << endl;
	cout << "��������������������  ��          8.�ָ���ɾ��Ϣ        ��  �������������������" << endl;
	cout << "��������������������  ��          0.��ȫ�˳�ϵͳ        ��  �������������������" << endl;

	cout << "\n\t\t\n\t\t��ѡ��";
}

//�k�k�k�k�k�k�k�k�k�k�k�k���Һ����k�k�k�k�k�k�k�k�k�k�k�k
void Studentmassage::Find()
{
	char name[20], Id[10];
	int x;
	Student * p = NULL;
	cout << "\n\t\t*********************************\n";
	cout << "\t\t�� 1.��ѧ������������\n\t\t�� 2.��ѧ��ѧ�Ų���";
	cout << "\n\t\t*********************************\n��ѡ��";
	cin >> x;
	switch (x)
	{
	case 1: {cout << "\t\t������Ҫ���ҵ�ѧ����������"; cin >> name;
		if (p = FindItem(name))
		{
			p->Next->Show();
			cout << "���������ַ�����������";
			_getch();
		}
		else
		{
			cout << "\t\tû���ҵ���������ѧ����" << '\n' << endl;
			cout << "���������ַ�����������";
			_getch();
		}
	}break;
	case 2:
	{
		cout << "\t\t������Ҫ���ҵ�ѧ����ѧ�ţ�"; cin >> Id;
		if (p = FindID(Id))
		{
			p->Next->Show();
			cout << "���������ַ�����������";
			_getch();
		}
		else
		{
			cout << "\t\tû���ҵ���ѧ�ŵ�ѧ����" << '\n' << endl;
			cout << "���������ַ�����������";
			_getch();
		}
	}break;
	}

}

//�k�k�k�k�k�k�k�k�k�k�k�k�޸���Ϣ�k�k�k�k�k�k�k�k�k�k�k�k
void Studentmassage::ModifyItem()     //�޸���Ϣ
{
	char name[20];
	Student * p = NULL;
	cout << "\t\t������Ҫ�޸ĵ��˵�����:"; cin >> name;
	if (p = FindItem(name))
	{
		cout << "\t\t���ҵ�ѧ������Ϣ���������µ���Ϣ!" << endl;
		p->Next->Input();
		cout << "�޸ĳɹ���" << endl;
		cout << "���������ַ�����������";
		_getch();
	}
	else
	{
		cout << "\t\tû���ҵ�!" << endl;
		cout << "���������ַ�����������";
		_getch();
	}
}

//�k�k�k�k�k�k�k�k�k�k�k�k����ɾ����Ϣ�k�k�k�k�k�k�k�k�k�k�k�k
void Studentmassage::SaveRemove(Student *p)
{
	out.open("remove.txt",ios::out);
	out << p->name << "\t" << p->Id << "\t" << p->math << "\t"
		<< p->chemi << "\t" << p->physics << "\t" << p->internet << "\t" << p->English << "\t";
	out.close();
}

//�k�k�k�k�k�k�k�k�k�k�k�k�ָ���Ϣ�k�k�k�k�k�k�k�k�k�k�k�k
void Studentmassage::Recover()
{
	infile.open("remove.txt");
	if (!infile.is_open())
	{
		cout << "û��ɾ����Ϣ!" << endl;
		return;
	}
	if (infile.peek() != EOF)
	{
		infile >> End->name >> End->Id >> End->math >>
			End->chemi >> End->physics >> End->internet >> End->English;
		End->Calculate();
		End->Next = new Student;
		End = End->Next;
		cout << "�ָ��ɹ���" << endl;
	}
	else
		cout << "û��ɾ������Ϣ��" << endl;
	infile.close();
	cout << "���������ַ�����������";
	_getch();
}

//�k�k�k�k�k�k�k�k�k�k�k�kɾ����Ϣ�k�k�k�k�k�k�k�k�k�k�k�k
void Studentmassage::RemoveItem()         // ɾ����Ϣ
{
	char name[20];
	Student * p = NULL, *temp = NULL;
	cout << "\t\t������Ҫɾ����ѧ��������:" << endl; cin >> name;
	if (p = FindItem(name))
	{
		SaveRemove(p->Next);
		temp = p->Next;
		p->Next = p->Next->Next;
		delete temp;
		cout << "\t\tɾ���ɹ�!" << endl;
		cout << "���������ַ�����������";
		_getch();
	}
	else
	{
		cout << "\t\tû���ҵ�!" << endl;
		cout << "���������ַ�����������";
		_getch();
	}
}

//�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k
void Studentmassage::Swap(Student *p1, Student *p2)//��������combox������������
{
	Student *temp = new Student;
	strcpy(temp->name, p1->name);
	strcpy(temp->Id, p1->Id);
	temp->math = p1->math;
	temp->chemi = p1->chemi;
	temp->physics = p1->physics;
	temp->internet = p1->internet;
	temp->English = p1->English;
	temp->sum = p1->sum;
	temp->aver = p1->aver;

	strcpy(p1->name, p2->name);
	strcpy(p1->Id, p2->Id);
	p1->math = p2->math;
	p1->chemi = p2->chemi;
	p1->physics = p2->physics;
	p1->internet = p2->internet;
	p1->English = p2->English;
	p1->sum = p2->sum;
	p1->aver = p2->aver;

	strcpy(p2->name, temp->name);
	strcpy(p2->Id, temp->Id);
	p2->math = temp->math;
	p2->chemi = temp->chemi;
	p2->physics = temp->physics;
	p2->internet = temp->internet;
	p2->English = temp->English;
	p2->sum = temp->sum;
	p2->aver = temp->aver;
}

//�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k
int Studentmassage::ListCount()//ͳ�Ƶ�ǰ����ļ�¼����������һ������
{
	if (!Head)
		return 0;
	int n = 0;
	for (Student * p = Head->Next; p != End; p = p->Next)
	{
		n++;
	}
	return n;
}

//�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k
void Studentmassage::Sort()//�Ե�ǰ����������� 
{
	cout << "Sorting..." << endl;
	Student *p = NULL, *p1 = NULL, *k = NULL;
	int n = Studentmassage::ListCount();
	if (n < 2)
		return;
	for (p = Head->Next; p != End; p = p->Next)
		for (k = p->Next; k != End; k = k->Next)
		{
			if (p->sum > k->sum)
			{
				Studentmassage::Swap(p, k);
			}
		}
	cout << "�Ѱ��ܷ�����������ɣ��鿴��ѡ����ʾ" << endl;
	_getch();
	return;
}


//�k�k�k�k�k�k�k�k�k�k�k�kͳ�ƺ����k�k�k�k�k�k�k�k�k�k�k�k 
void Studentmassage::statistic()
{
	int a1 = 0, a2 = 0, a3 = 0, a4 = 0, a5 = 0;
	int s1, s2, s3, s4, s5, s6, h1, h2, h3, h4, h5, h6, w1, w2, w3, w4, w5, w6, wl1, wl2, wl3, wl4, wl5, wl6, y1, y2, y3, y4, y5, y6;
	s1 = s2 = s3 = s4 = s5 = s6 = h1 = h2 = h3 = h4 = h5 = h6 = w1 = w2 = w3 = w4 = w5 = w6 = wl1 = wl2 = wl3 = wl4 = wl5 = wl6 = y1 = y2 = y3 = y4 = y5 = y6 = 0;
	int b1, b2, b3, b4, b5, b6, c1, c2, c3, c4, c5, c6, d1, d2, d3, d4, d5, d6, e1, e2, e3, e4, e5, e6, f1, f2, f3, f4, f5, f6;
	b1 = b2 = b3 = b4 = b5 = b6 = c1 = c2 = c3 = c4 = c5 = c6 = d1 = d2 = d3 = d4 = d5 = d6 = e1 = e2 = e3 = e4 = e5 = e6 = f1 = f2 = f3 = f4 = f5 = f6 = 0;
	int avermath, averchemi, averphysics, averinternet, averEnglish;
	int n = Studentmassage::ListCount();
	for (Student * p = Head->Next; p != End; p = p->Next)
	{
		a1 = a1 + p->math;
		{
			if (p->math == 100) { s1++; b1 = (s1 / n) * 100; }
			else if (p->math >= 90 && p->math <= 99) { s2++; b2 = (s2 / n) * 100; }
			else if (p->math >= 80 && p->math <= 89) { s3++; b3 = (s3 / n) * 100; }
			else if (p->math >= 70 && p->math <= 79) { s4++; b4 = (s4 / n) * 100; }
			else if (p->math >= 60 && p->math <= 69) { s5++; b5 = (s5 / n) * 100; }
			else { s6++; b6 = (s6 / n) * 100; }
		}
		a2 = a2 + p->chemi;
		{
			if (p->chemi == 100) { h1++; c1 = (h1 / n) * 100; }
			else if (p->chemi >= 90 && p->chemi <= 99) { h2++; c2 = (h2 / n) * 100; }
			else if (p->chemi >= 80 && p->chemi <= 89) { h3++; c3 = (h3 / n) * 100; }
			else if (p->chemi >= 70 && p->chemi <= 79) { h4++; c4 = (h4 / n) * 100; }
			else if (p->chemi >= 60 && p->chemi <= 69) { h5++; c5 = (h5 / n) * 100; }
			else { h6++; c6 = (h6 / n) * 100; }
		}
		a3 = a3 + p->physics;
		{
			if (p->physics == 100) { w1++; d1 = (w1 / n) * 100; }
			else if (p->physics >= 90 && p->physics <= 99) { w2++; d2 = (w2 / n) * 100; }
			else if (p->physics >= 80 && p->physics <= 89) { w3++; d3 = (w3 / n) * 100; }
			else if (p->physics >= 70 && p->physics <= 79) { w4++; d4 = (w4 / n) * 100; }
			else if (p->physics >= 60 && p->physics <= 69) { w5++; d5 = (w5 / n) * 100; }
			else { w6++; d6 = (w6 / n) * 100; }
		}
		a4 = a4 + p->internet;
		{
			if (p->internet == 100) { wl1++; e1 = (wl1 / n) * 100; }
			else if (p->internet >= 90 && p->internet <= 99) { wl2++; e2 = (wl2 / n) * 100; }
			else if (p->internet >= 80 && p->internet <= 89) { wl3++; e3 = (wl3 / n) * 100; }
			else if (p->internet >= 70 && p->internet <= 79) { wl4++; e4 = (wl4 / n) * 100; }
			else if (p->internet >= 60 && p->internet <= 69) { wl5++; e5 = (wl5 / n) * 100; }
			else { wl6++; e6 = (wl6 / n) * 100; }
		}
		a5 = a5 + p->English;
		{
			if (p->English == 100) { y1++; f1 = (y1 / n) * 100; }
			else if (p->English >= 90 && p->English <= 99) { y2++; f2 = (y2 / n) * 100; }
			else if (p->English >= 80 && p->English <= 89) { y3++; f3 = (y3 / n) * 100; }
			else if (p->English >= 70 && p->English <= 79) { y4++; f4 = (y4 / n) * 100; }
			else if (p->English >= 60 && p->English <= 69) { y5++; f5 = (y5 / n) * 100; }
			else y6++; f6 = (y6 / n) * 100;
		}
	}
	avermath = a1 / n;
	averchemi = a2 / n;
	averphysics = a3 / n;
	averinternet = a4 / n;
	averEnglish = a5 / n;

	cout << "��ѧ�γ�ƽ���ɼ�Ϊ��" << avermath << endl;
	cout << "��ѧ�γ�ƽ���ɼ�Ϊ��" << averchemi << endl;
	cout << "����γ�ƽ���ɼ�Ϊ��" << averphysics << endl;
	cout << "����γ�ƽ���ɼ�Ϊ��" << averinternet << endl;
	cout << "Ӣ��γ�ƽ���ɼ�Ϊ��" << averEnglish << endl << endl << endl;

	cout << "��ѧ100��������" << s1 << "ռ�ȣ�" << b1 << "%" << endl;
	cout << "90~99����������" << s2 << "ռ�ȣ�" << b2 << "%" << endl;
	cout << "80~89����������" << s3 << "ռ�ȣ�" << b3 << "%" << endl;
	cout << "70~79����������" << s4 << "ռ�ȣ�" << b4 << "%" << endl;
	cout << "60~69����������" << s5 << "ռ�ȣ�" << b5 << "%" << endl;
	cout << "59�ּ�����������" << s6 << "ռ�ȣ�" << b6 << "%" << endl << endl << endl;

	cout << "��ѧ100��������" << h1 << "ռ�ȣ�" << c1 << "%" << endl;
	cout << "90~99����������" << h2 << "ռ�ȣ�" << c2 << "%" << endl;
	cout << "80~89����������" << h3 << "ռ�ȣ�" << c3 << "%" << endl;
	cout << "70~79����������" << h4 << "ռ�ȣ�" << c4 << "%" << endl;
	cout << "60~69����������" << h5 << "ռ�ȣ�" << c5 << "%" << endl;
	cout << "59�ּ�����������" << h6 << "ռ�ȣ�" << c6 << "%" << endl << endl << endl;

	cout << "����100��������" << w1 << "ռ�ȣ�" << d1 << "%" << endl;
	cout << "90~99����������" << w2 << "ռ�ȣ�" << d2 << "%" << endl;
	cout << "80~89����������" << w3 << "ռ�ȣ�" << d3 << "%" << endl;
	cout << "70~79����������" << w4 << "ռ�ȣ�" << d4 << "%" << endl;
	cout << "60~69����������" << w5 << "ռ�ȣ�" << d5 << "%" << endl;
	cout << "59�ּ�����������" << w6 << "ռ�ȣ�" << d6 << "%" << endl << endl << endl;

	cout << "����100��������" << wl1 << "ռ�ȣ�" << e1 << "%" << endl;
	cout << "90~99����������" << wl2 << "ռ�ȣ�" << e2 << "%" << endl;
	cout << "80~89����������" << wl3 << "ռ�ȣ�" << e3 << "%" << endl;
	cout << "70~79����������" << wl4 << "ռ�ȣ�" << e4 << "%" << endl;
	cout << "60~69����������" << wl5 << "ռ�ȣ�" << e5 << "%" << endl;
	cout << "59�ּ�����������" << wl6 << "ռ�ȣ�" << e6 << "%" << endl << endl << endl;

	cout << "Ӣ��100��������" << y1 << "ռ�ȣ�" << f1 << "%" << endl;
	cout << "90~99����������" << y2 << "ռ�ȣ�" << f2 << "%" << endl;
	cout << "80~89����������" << y3 << "ռ�ȣ�" << f3 << "%" << endl;
	cout << "70~79����������" << y4 << "ռ�ȣ�" << f4 << "%" << endl;
	cout << "60~69����������" << y5 << "ռ�ȣ�" << f5 << "%" << endl;
	cout << "59�ּ�����������" << y6 << "ռ�ȣ�" << f6 << "%" << endl << endl << endl;
	system("pause");
	return;
}



//�k�k�k�k�k�k�k�k�k�k�k���溯���k�k�k�k�k�k�k�k�k�k�k�k�k
void Studentmassage::Save()
{
	out.open("sort.txt");
	for (Student *p = Head->Next; p != End; p = p->Next)
	{
		out << p->name << "\t" << p->Id << "\t" << p->math << "\t"
			<< p->chemi << "\t" << p->physics << "\t" << p->internet << "\t" << p->English;
		if (p->Next != End)
			out << "\n";
	}
	out.close();
}


//�k�k�k�k�k�k�k�k�k�k�k�ָ������k�k�k�k�k�k�k�k�k�k�k�k�k
bool Studentmassage::Read()
{
	infile.open("sort.txt");
	if (!infile.is_open())
		return false;

	while (infile.peek() != EOF)
	{
		infile >> End->name >> End->Id >> End->math >>
			End->chemi >> End->physics >> End->internet >> End->English;
		End->Calculate();
		End->Next = new Student;
		End = End->Next;
	}
	infile.close();
	return true;
}



//�k�k�k�k�k�k�k�k�k�k�k�k�������k�k�k�k�k�k�k�k�k�k�k�k
using namespace std;
int main()
{
	int x, i = 0;
	bool quit = false;
	cout << "\t\t���������������������������" << endl;
	for (i = 0; i < 3; i++)
		cout << "\t\t��\t\t\t\t\t\t  ��" << endl;
	cout << "\t\t�����  ��ӭ����ѧ���ɼ�����ϵͳ  ��������" << endl;
	for (i = 0; i < 3; i++)
		cout << "\t\t��\t\t\t\t\t\t  ��" << endl;
	cout << "\t\t���������������������������\n" << endl;;
	Studentmassage Grade;
	cout << "���������ʼ����";
	_getch();
	while (!quit)
	{
		system("cls");
		Grade.ShowMenu();
		cin >> x;
		switch (x)
		{
		case 0:quit = true; break;
		case 1:Grade.AddItem(); break;/*����*/
		case 2:Grade.Display(); break;/*��ʾ*/
		case 3:Grade.Sort(); break;/*����*/
		case 4:Grade.Find(); break;/*����*/
		case 5:Grade.RemoveItem(); break;/*ɾ��*/
		case 6:Grade.ModifyItem(); break;/*�޸�*/
		case 7:Grade.statistic(); break;/*ͳ��*/
		case 8:Grade.Recover(); break;
		}
	}
	return 0;
}
