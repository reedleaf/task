/*
################################
.      ԭ����д�����ſɿ���
.      ע����ϸ�����빤����
.      ˮƽһ���������׶���
.      ��ѭ�̲ģ��������١�
.          < ReedLeaf >
.        QQ : 1020273485
.  https://codefox.taobao.com
################################

.���ԡ�����C++
.���⡡������ҵ����ϵͳ 
.��������������Ŀ����
.Ҫ�󡡣�������Ŀ����

ע��:
	��1�������ǰ��տͻ���������ϸҪ��ȥ��д��,�շ��ǰ��յ�ʱ��Ҫ������շѵġ����Ժ���Ҫ����ӹ��������ǲ�����,

	��2�� �õ�����󾡿���ԣ����������,�������ǹ������ܴ�,����һֱ��ʱ�����
	         �������û�һ���º��ҹ�������޸ĵ�����(��������һ���¶��ڸ����أ�)���������½�

	��3�����ǲ������̻��������,С�������������,������𲻹���Щ�ͻ���Ѵ�д�͸�����Ϊһ̸,��ͷ�����ǵõ��Ļ���һ��������
	         �����������Ķ���
*/
/* 
��Ŀ 10���γ���ҵ����ϵͳ 
Ҫ�� 
1��ѧ�����Խ��γ���ҵ��ʵ�鱨�����ҵ���ͣ��� WORD��TXT �ļ���ʽΪ������֧����
�������ӡ��޸ġ�ɾ������ѯ�� 
2����ʦ���Զ���ҵ�������֣���֧�ֶ�ѧ���ύ��ҵ���в�ѯ�Ȳ����� 
3�����в鿴��塣 

*/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

//��ʼ��ʦ����
#define ADMINPASSWORD "123456"

//ѧ����
class Student {
public:
	Student() :_score(-1) {}
	~Student() {}

public:
	void setHomework(string homework);
	void setScore(float score);
	void setName(string name);

public:
	string getHomework() { return _homework; }
	float getScore() { return _score; }
	string getName() { return _name; }

private:
	string _name;				//����
	string _homework;		//��ҵ
	float _score;					//�ɼ�
};
void Student::setHomework(string homework)
{
	_homework = homework;
}
void Student::setScore(float score)
{
	_score = score;
}
void Student::setName(string name)
{
	_name = name;
}

//������
class Operator {
public:
	//����ѧ��
	auto findInfo(string name)
	{
		for (auto it = student.begin(); it != student.end(); ++it)
		{
			if (it->getName() == name)
				return it;
		}
		return student.end();
	}

public:
	//add
	void addStudentInfo()
	{
		while (true)
		{
			int choice;
			string name;
			string homework;
			Student s;

			cout << "������";
			cin >> name;
			s.setName(name);

			cout << "��ҵ��";
			cin >> homework;
			s.setHomework(homework);

			student.push_back(s);
			cout << "�Ƿ��������0:��  1:�ǣ�";
			cin >> choice;
			if (!choice)
				break;
		}
	}
	//del
	void delStudentInfo()
	{
		string name;
		cout << "����ѧ��������";
		cin >> name;
		auto it = findInfo(name);
		if (it != student.end()) 
		{
			student.erase(it);
			cout << "ɾ���ɹ���" << endl;
		}
		else
			cout << "û�и�ѧ����" << endl;
	}
	//update
	void updateStudentInfo()
	{
		string name;
		cout << "����ѧ��������";
		cin >> name;
		auto it = findInfo(name);
		if (it != student.end())
		{
			string homework;
			cout << "��������ҵ��";
			cin >> homework;
			it->setHomework(homework);
			cout << "�޸���ɣ�" << endl;
		}
		else
			cout << "û�����ѧ����" << endl;
	}
	//query
	void queryStudentInfo()
	{
		string name;
		cout << "����ѧ��������";
		cin >> name;
		auto it = findInfo(name);
		if (it != student.end())
		{
			cout << "������" << it->getName() << endl;
			cout << "��ҵ��" << it->getHomework() << endl;
			if (it->getScore() == -1)
				cout << "�ɼ���δ��" << endl;
			else
				cout << "�ɼ���" << it->getScore()<<endl;
		}
	}

public:
	/*teacherOperator*/
	void teacherSetSCore()
	{
		for (int i = 0; i < student.size(); ++i)
		{
			float score;
			cout << student[i].getName() << "��" << student[i].getHomework() << endl;
			cout << "���֣�";
			cin >> score;
			student[i].setScore(score);
		}
		if (student.empty())
			cout << "û��ѧ���Ͻ���ҵ��" << endl;
	}

public:
	//save
	void save()
	{
		fstream outfile;
		outfile.open("homework.txt", ios::out);
		if (!outfile.is_open())
		{
			cout << "�ļ���ʧ�ܣ�" << endl;
			return;
		}

		for (int i = 0; i < student.size(); ++i)
		{
			outfile << student[i].getName() << "\t"
				<< student[i].getHomework() << "\t"
				<< student[i].getScore();
			if (i + 1 != student.size())
				outfile << "\n";
		}
		outfile.close();
	}
	//read
	void read()
	{
		fstream infile("homework.txt");

		while (infile.peek() != EOF)
		{
			string name;
			string homework;
			float score;
			Student s;

			infile >> name >> homework >> score;

			s.setName(name);
			s.setHomework(homework);
			s.setScore(score);

			student.push_back(s);
		}
		infile.close();
	}


private:
	vector<Student> student;
};



/* studentMenu */
void studnetMenu()
{
	Operator stu;
	stu.read();
	while (true)
	{
		system("cls");
		int choice;
		cout << "*****ѧ������******" << endl;
		cout << "<0>�˳�ѧ������" << endl;
		cout << "<1>�����ҵ" << endl;
		cout << "<2>ɾ����ҵ" << endl;
		cout << "<3>�޸���ҵ" << endl;
		cout << "<4>��ѯ��ҵ" << endl;
		cout << "ѡ��(0-4)��";
		cin >> choice;
		switch (choice)
		{
		case 0:
			stu.save();
			return;
		case 1:
			stu.addStudentInfo();
			break;
		case 2:
			stu.delStudentInfo();
			break;
		case 3:
			stu.updateStudentInfo();
			break;
		case 4:
			stu.queryStudentInfo();
			break;
		default:cout << "�������" << endl;
			break;
		}
		system("pause");
	}
}

/*  teacherMenu  */
void teacherMenu()
{
	Operator stu;
	stu.read();
	while (true)
	{
		system("cls");
		int choice;
		cout << "*****��ʦ����******" << endl;
		cout << "<0>�˳���ʦ����" << endl;
		cout << "<1>�����ҵ" << endl;
		cout << "<2>ɾ����ҵ" << endl;
		cout << "<3>�޸���ҵ" << endl;
		cout << "<4>��ѯ��ҵ" << endl;
		cout << "<5>��ҵ����" << endl;
		cout << "ѡ��(0-4)��";
		cin >> choice;
		switch (choice)
		{
		case 0:
			stu.save();
			return;
		case 1:
			stu.addStudentInfo();
			break;
		case 2:
			stu.delStudentInfo();
			break;
		case 3:
			stu.updateStudentInfo();
			break;
		case 4:
			stu.queryStudentInfo();
			break;
		case 5:
			stu.teacherSetSCore();
			break;
		default:cout << "�������" << endl;
			break;
		}
		system("pause");
	}
}


/*   menu  */
void menu()
{
	while (true)
	{
		system("cls");
		int choice;
		cout << "<0>�˳�ϵͳ" << endl;
		cout << "<1>ѧ������" << endl;
		cout << "<2>��ʦ����" << endl;
		cin >> choice;
		switch (choice)
		{
		case 0:
			return;
		case 1:
			studnetMenu();
			break;
		case 2:
		{
			//��ʦ��¼Ҫ��������
			string password;
			cout << "�������룺";
			cin >> password;
			if (password == ADMINPASSWORD)
				teacherMenu();
			else
				cout << "�������" << endl;
		}
			break;
		default:
			break;
		}
		system("pause");
	}
}

int main()
{
	menu();
	system("pause");
	return 0;
}
