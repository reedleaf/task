/*################################
.      原创代写，诚信可靠；
.      注释详细，编码工整；
.      水平一流，讲解易懂；
.      遵循教材，绝不超纲。
.          < ReedLeaf >
.        QQ : 1020273485
.  https://codefox.taobao.com
################################

.语言　：　C++
.课题　：　xxxxxxxxxxxxxxxxxxx
.概述　：　见题目描述
.要求　：　见题目描述

注明:
	《1》我们是按照客户给出的详细要求去编写的,收费是按照当时的要求合理收费的。所以后期要求添加功能我们是不做的,

	《2》 拿到程序后尽快测试，并提出问题,由于我们工作量很大,不会一直长时间服务，
			 发生过用户一个月后半夜让我们修改的事情(请问她这一个月都在干嘛呢？)所以望能谅解

	《3》我们不包括教会这个程序,小问题可以问我们,定当解答不过有些客户会把代写和辅导混为一谈,到头来我们得到的还是一个差评，
			 所以请认真阅读。
*/
#define _CRT_SECURE_NO_WARNINGS
# include <iostream>
# include <fstream>
# include <string.h>
#include <conio.h>//用getch();
using namespace std;
int i;

//﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌Student类﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌
class Student
{
public:
	char name[20];
	char Id[20];
	int math;       //数学
	int chemi;       //化学
	int physics;       //物理 
	int internet;      //网络
	int English;      //英语 
	int sum;        //总分   
	int aver;      //平均分  
	Student * Next;
	void Input()
	{
		cout << "\t\t请输入学生的姓名：";  cin >> name;
		cout << "\t\t请输入学生的学号：";  cin >> Id;
		cout << "\t\t请输入数学成绩：";  cin >> math;
		cout << "\t\t请输入化学成绩：";  cin >> chemi;
		cout << "\t\t请输入物理成绩：";  cin >> physics;
		cout << "\t\t请输入网络成绩：";  cin >> internet;
		cout << "\t\t请输入英语成绩：";  cin >> English;
	}
	void Calculate()
	{
		sum = math + chemi + physics + internet + English;
		aver = sum / 5;
	}
	void Show()
	{
		cout << "姓名:" << name << endl << "学号:" << Id << endl << "数学：" << math << endl
			<< "化学：" << chemi << endl << "物理：" << physics << endl << "网络：" << internet << endl << "英语：" << English << endl << "总成绩:" << sum << endl << "平均分：" << aver << endl << endl << endl;
	}
};

//﹌﹌﹌﹌﹌﹌﹌﹌﹌Studentmassage类﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌
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
		cout << "输入任意字符！继续……";
		_getch();
	}
	void AddItem()
	{
		End->Input();
		End->Calculate();
		End->Next = new Student;
		End = End->Next;
		cout << "保存成功!" << endl;
		cout << "输入任意字符！继续……";
		_getch();
	}
private:
	Student * Head, *End;
	ofstream out;
	ifstream infile;
	Student *FindItem(char * name)
	{
		for (Student * p = Head; p->Next != End; p = p->Next)//匹配成功则返回上一个指针，不成功就返回空
			if (!strcmp(p->Next->name, name))return p;
		return NULL;
	}
	Student *FindID(char * Id)
	{
		for (Student * p = Head; p->Next != End; p = p->Next)//匹配成功则返回上一个指针，不成功就返回空
			if (!strcmp(p->Next->Id, Id))return p;
		return NULL;
	}
};



//﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌构造函数﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌
Studentmassage::Studentmassage()
{
	Head = new Student;
	Head->Next = new Student;
	End = Head->Next;
	if (!Read())
		cout << "这是一个新系统，无学生信息。请先输入。" << endl;
	else
		cout << "\t\t读取学生信息成功!" << endl;
}

//﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌析构函数﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌
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

//﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌菜单﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌
void Studentmassage::ShowMenu()
{
	cout << "********************************************************************************" << endl;
	cout << "〓〓〓〓〓〓〓〓〓〓  ☆   学 生 成 绩 管 理 系  统     ☆  〓〓〓〓〓〓〓〓〓〓" << endl;
	cout << "〓〓〓〓〓〓〓★★★★★         ★★★★★★★         ★★★★★〓〓〓〓〓〓〓" << endl;
	cout << "〓〓〓〓〓〓〓〓〓★  ☆          1.增加学生成绩        ☆  ★〓〓〓〓〓〓〓〓〓" << endl;
	cout << "〓〓〓〓〓〓〓〓〓★  ☆          2.显示学生成绩        ☆  ★〓〓〓〓〓〓〓〓〓" << endl;
	cout << "〓〓〓〓〓〓〓〓〓★  ☆          3.排序学生成绩        ☆  ★〓〓〓〓〓〓〓〓〓" << endl;
	cout << "〓〓〓〓〓〓〓〓〓★  ☆          4.查找学生成绩        ☆  ★〓〓〓〓〓〓〓〓〓" << endl;
	cout << "〓〓〓〓〓〓〓〓〓★  ☆          5.删除学生成绩        ☆  ★〓〓〓〓〓〓〓〓〓" << endl;
	cout << "〓〓〓〓〓〓〓〓〓★  ☆          6.修改学生信息        ☆  ★〓〓〓〓〓〓〓〓〓" << endl;
	cout << "〓〓〓〓〓〓〓〓〓★  ☆          7.统计学生信息        ☆  ★〓〓〓〓〓〓〓〓〓" << endl;
	cout << "〓〓〓〓〓〓〓〓〓★  ☆          8.恢复已删信息        ☆  ★〓〓〓〓〓〓〓〓〓" << endl;
	cout << "〓〓〓〓〓〓〓〓〓★  ☆          0.安全退出系统        ☆  ★〓〓〓〓〓〓〓〓〓" << endl;

	cout << "\n\t\t\n\t\t请选择：";
}

//﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌查找函数﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌
void Studentmassage::Find()
{
	char name[20], Id[10];
	int x;
	Student * p = NULL;
	cout << "\n\t\t*********************************\n";
	cout << "\t\t※ 1.按学生的姓名查找\n\t\t※ 2.按学生学号查找";
	cout << "\n\t\t*********************************\n请选择：";
	cin >> x;
	switch (x)
	{
	case 1: {cout << "\t\t请输入要查找的学生的姓名："; cin >> name;
		if (p = FindItem(name))
		{
			p->Next->Show();
			cout << "输入任意字符！继续……";
			_getch();
		}
		else
		{
			cout << "\t\t没有找到该姓名的学生！" << '\n' << endl;
			cout << "输入任意字符！继续……";
			_getch();
		}
	}break;
	case 2:
	{
		cout << "\t\t请输入要查找的学生的学号："; cin >> Id;
		if (p = FindID(Id))
		{
			p->Next->Show();
			cout << "输入任意字符！继续……";
			_getch();
		}
		else
		{
			cout << "\t\t没有找到该学号的学生！" << '\n' << endl;
			cout << "输入任意字符！继续……";
			_getch();
		}
	}break;
	}

}

//﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌修改信息﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌
void Studentmassage::ModifyItem()     //修改信息
{
	char name[20];
	Student * p = NULL;
	cout << "\t\t请输入要修改的人的姓名:"; cin >> name;
	if (p = FindItem(name))
	{
		cout << "\t\t已找到学生的信息，请输入新的信息!" << endl;
		p->Next->Input();
		cout << "修改成功！" << endl;
		cout << "输入任意字符！继续……";
		_getch();
	}
	else
	{
		cout << "\t\t没有找到!" << endl;
		cout << "输入任意字符！继续……";
		_getch();
	}
}

//﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌保存删除信息﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌
void Studentmassage::SaveRemove(Student *p)
{
	out.open("remove.txt",ios::out);
	out << p->name << "\t" << p->Id << "\t" << p->math << "\t"
		<< p->chemi << "\t" << p->physics << "\t" << p->internet << "\t" << p->English << "\t";
	out.close();
}

//﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌恢复信息﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌
void Studentmassage::Recover()
{
	infile.open("remove.txt");
	if (!infile.is_open())
	{
		cout << "没有删除信息!" << endl;
		return;
	}
	if (infile.peek() != EOF)
	{
		infile >> End->name >> End->Id >> End->math >>
			End->chemi >> End->physics >> End->internet >> End->English;
		End->Calculate();
		End->Next = new Student;
		End = End->Next;
		cout << "恢复成功！" << endl;
	}
	else
		cout << "没有删除的信息！" << endl;
	infile.close();
	cout << "输入任意字符！继续……";
	_getch();
}

//﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌删除信息﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌
void Studentmassage::RemoveItem()         // 删除信息
{
	char name[20];
	Student * p = NULL, *temp = NULL;
	cout << "\t\t请输入要删除的学生的姓名:" << endl; cin >> name;
	if (p = FindItem(name))
	{
		SaveRemove(p->Next);
		temp = p->Next;
		p->Next = p->Next->Next;
		delete temp;
		cout << "\t\t删除成功!" << endl;
		cout << "输入任意字符！继续……";
		_getch();
	}
	else
	{
		cout << "\t\t没有找到!" << endl;
		cout << "输入任意字符！继续……";
		_getch();
	}
}

//﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌
void Studentmassage::Swap(Student *p1, Student *p2)//交换两个combox变量的数据域
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

//﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌
int Studentmassage::ListCount()//统计当前链表的记录总数，返回一个整数
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

//﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌
void Studentmassage::Sort()//对当前链表进行排序 
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
	cout << "已按总分升序排序完成！查看请选择显示" << endl;
	_getch();
	return;
}


//﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌统计函数﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌ 
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

	cout << "数学课程平均成绩为：" << avermath << endl;
	cout << "化学课程平均成绩为：" << averchemi << endl;
	cout << "物理课程平均成绩为：" << averphysics << endl;
	cout << "网络课程平均成绩为：" << averinternet << endl;
	cout << "英语课程平均成绩为：" << averEnglish << endl << endl << endl;

	cout << "数学100分人数：" << s1 << "占比：" << b1 << "%" << endl;
	cout << "90~99分数人数：" << s2 << "占比：" << b2 << "%" << endl;
	cout << "80~89分数人数：" << s3 << "占比：" << b3 << "%" << endl;
	cout << "70~79分数人数：" << s4 << "占比：" << b4 << "%" << endl;
	cout << "60~69分数人数：" << s5 << "占比：" << b5 << "%" << endl;
	cout << "59分及以下人数：" << s6 << "占比：" << b6 << "%" << endl << endl << endl;

	cout << "化学100分人数：" << h1 << "占比：" << c1 << "%" << endl;
	cout << "90~99分数人数：" << h2 << "占比：" << c2 << "%" << endl;
	cout << "80~89分数人数：" << h3 << "占比：" << c3 << "%" << endl;
	cout << "70~79分数人数：" << h4 << "占比：" << c4 << "%" << endl;
	cout << "60~69分数人数：" << h5 << "占比：" << c5 << "%" << endl;
	cout << "59分及以下人数：" << h6 << "占比：" << c6 << "%" << endl << endl << endl;

	cout << "物理100分人数：" << w1 << "占比：" << d1 << "%" << endl;
	cout << "90~99分数人数：" << w2 << "占比：" << d2 << "%" << endl;
	cout << "80~89分数人数：" << w3 << "占比：" << d3 << "%" << endl;
	cout << "70~79分数人数：" << w4 << "占比：" << d4 << "%" << endl;
	cout << "60~69分数人数：" << w5 << "占比：" << d5 << "%" << endl;
	cout << "59分及以下人数：" << w6 << "占比：" << d6 << "%" << endl << endl << endl;

	cout << "网络100分人数：" << wl1 << "占比：" << e1 << "%" << endl;
	cout << "90~99分数人数：" << wl2 << "占比：" << e2 << "%" << endl;
	cout << "80~89分数人数：" << wl3 << "占比：" << e3 << "%" << endl;
	cout << "70~79分数人数：" << wl4 << "占比：" << e4 << "%" << endl;
	cout << "60~69分数人数：" << wl5 << "占比：" << e5 << "%" << endl;
	cout << "59分及以下人数：" << wl6 << "占比：" << e6 << "%" << endl << endl << endl;

	cout << "英语100分人数：" << y1 << "占比：" << f1 << "%" << endl;
	cout << "90~99分数人数：" << y2 << "占比：" << f2 << "%" << endl;
	cout << "80~89分数人数：" << y3 << "占比：" << f3 << "%" << endl;
	cout << "70~79分数人数：" << y4 << "占比：" << f4 << "%" << endl;
	cout << "60~69分数人数：" << y5 << "占比：" << f5 << "%" << endl;
	cout << "59分及以下人数：" << y6 << "占比：" << f6 << "%" << endl << endl << endl;
	system("pause");
	return;
}



//﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌保存函数﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌
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


//﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌恢复函数﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌
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



//﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌主函数﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌
using namespace std;
int main()
{
	int x, i = 0;
	bool quit = false;
	cout << "\t\t§§§§§§§§§§§§§§§§§§§§§§§§§§" << endl;
	for (i = 0; i < 3; i++)
		cout << "\t\t◎\t\t\t\t\t\t  ◎" << endl;
	cout << "\t\t◎★★★★【  欢迎进入学生成绩管理系统  】★★★★◎" << endl;
	for (i = 0; i < 3; i++)
		cout << "\t\t◎\t\t\t\t\t\t  ◎" << endl;
	cout << "\t\t§§§§§§§§§§§§§§§§§§§§§§§§§§\n" << endl;;
	Studentmassage Grade;
	cout << "按任意键开始……";
	_getch();
	while (!quit)
	{
		system("cls");
		Grade.ShowMenu();
		cin >> x;
		switch (x)
		{
		case 0:quit = true; break;
		case 1:Grade.AddItem(); break;/*增加*/
		case 2:Grade.Display(); break;/*显示*/
		case 3:Grade.Sort(); break;/*排序*/
		case 4:Grade.Find(); break;/*查找*/
		case 5:Grade.RemoveItem(); break;/*删除*/
		case 6:Grade.ModifyItem(); break;/*修改*/
		case 7:Grade.statistic(); break;/*统计*/
		case 8:Grade.Recover(); break;
		}
	}
	return 0;
}
