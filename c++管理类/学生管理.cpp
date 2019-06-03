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
#include <iostream>
#include <vector>
#include <fstream>
#include<string>
#include <algorithm>

using namespace std;

#define ADMINPSW "admin"				//����Ա����
#define TEACHERPSW "teacher"		//��ʦ����

struct User
{
	string userName;
	string password;
	int num;								//ѧ���û����ѧ�ź�������Ϣ����
};
vector<User> user;			//�û�����
/*ѧ����
���� ���� ѧ�� �Ա� ��ϵ��ʽ ���Һ�
*/
class Student {
public:
	Student() {}
	~Student() {}

public:
	int _num;
	string _name;
	string _sex;
	string _phoneNumber;
	string _dormitory;
};

/*

�ɼ���
����ѧ�� �༶ �ɼ� ��ѧ�� �ܳɼ� ƽ���ɼ�
*/
class Grade {
public:
	Grade() {}
	~Grade() {}

public:
	int _num;			//ѧ�����
	vector<int> _credit;
	vector<float> _score;
	float _avgScore;
	int _totalCredit;
	float _totalScore;
	string _class;
};

/************************************************************************/
/*                          ������                             */
/************************************************************************/
class Operation
{
public:
	int curStudentIndex;
	int curUserIndex;
public:
	Operation() {}
	~Operation() {}

	//����Ա��Ϣ������
public:
	//¼��ѧ����Ϣ
	void addStudentInfo()
	{
		while (true)
		{
			//���� ���� ѧ�� �Ա� ��ϵ��ʽ ���Һ�
			char choice;
			Student stu;

			cout << "����ѧ��������";
			cin >> stu._name;
			cout << "����ѧ��ѧ�ţ�";
			cin >> stu._num;
			cout << "����ѧ���Ա�";
			cin >> stu._sex;
			cout << "����ѧ����ϵ��ʽ��";
			cin >> stu._phoneNumber;
			cout << "����ѧ�����Һţ�";
			cin >> stu._dormitory;

			student.push_back(stu);
			cout << "�Ƿ������(n:��  y:��)��";
			cin >> choice;
			cin.clear();
			cin.sync();
			if (choice == 'N' || choice == 'n')
				break;
		}
	}
	//ɾ��ѧ����Ϣ
	void deleteStudentInfo()
	{
		int num;
		bool tag = false;
		cout << "����ѧ����ţ�";
		cin >> num;

		//�൱�ڱ�������
		for (vector<Student>::iterator it = student.begin(); it != student.end(); ++it)
		{
			if (it->_num == num)
			{
				student.erase(it);//ɾ����������һ��Ԫ��
				tag = true;				//�����ѧ��,��ʾ�ҵ���
				break;
			}
		}
		if (!tag)
			cout << "û�����ѧ����" << endl;
	}
	//����ѧ����Ϣ�����ܳɼ���
	void sortStudentInfo_totalScore()
	{
		if (grade.empty())
		{
			cout << "������ɼ���" << endl;
			return;
		}
		vector<Grade> temp(grade);
		vector<Student> tempStu(student);
		//������(ð������)
		for (int i = 0; i < temp.size() - 1; ++i)
		{
			for (int j = 0; j < temp.size() - 1 - i; ++j)
			{
				if (temp[j]._totalScore > temp[j + 1]._totalScore)
					swap(temp[j], temp[j + 1]);//��������Ԫ��
			}
		}

		for (int i = 0; i < temp.size(); ++i)
		{
			for (int j = 0; j < student.size(); ++j)
			{
				if (student[i]._num == temp[i]._num)
				{
					tempStu[i] = student[j];
					break;
				}
			}
		}
		student.swap(tempStu);
		cout << "������ɣ�" << endl;
	}

	/************************************************************************/
	/*                       ��ʦ������                               */
	/************************************************************************/
public:
	//¼��ѧ���ɼ�
	void addStudentScore()
	{
		if (student.empty())
			cout << "û��ѧ����" << endl;
		//ѭ����Ϣvecot�����¼��
		for (int i = 0; i < student.size(); ++i)
		{
			cout << "*************************************" << endl;
			cout << "ѧ��" << i + 1 << endl;
			int choice;
			float _score;
			Grade temp;
			temp._totalCredit = 0;
			temp._totalScore = 0;
			temp._num = student[i]._num;
			cout << "����༶��";
			cin >> temp._class;
			cout << "����ѧ���ߵ���ѧ�ɼ���";
			cin >> _score;
			temp._score.push_back(_score);
			temp._totalScore += _score;
			cout << "����ѧ��������Ƴɼ���";
			cin >> _score;
			temp._score.push_back(_score);
			temp._totalScore += _score;
			cout << "����ѧ����ѧ����ɼ���";
			cin >> _score;
			temp._score.push_back(_score);
			temp._totalScore += _score;
			while (true)
			{
				float _credit;
				cout << "����ѧ������ѧ�֣�";
				cin >> _credit;
				temp._credit.push_back(_credit);
				temp._totalCredit += _credit;
				cout << "��0�˳����룬1������";
				cin >> choice;
				if (choice == 0)
					break;
			}
			temp._avgScore = temp._totalScore / temp._score.size();
			grade.push_back(temp);
		}
	}
	//�鿴�༶ƽ����
	void checkClassAvgScore()
	{
		bool tag = false;
		float sum = 0;
		int count = 0;
		string _class;
		cout << "����༶��" << endl;
		cin >> _class;
		for (int i = 0; i < grade.size(); ++i)
		{
			if (grade[i]._class == _class)
			{
				cout << grade[i]._totalScore << endl;
				sum += grade[i]._totalScore;
				count++;
				tag = true;
			}
		}
		if (!tag)
			cout << "û�а༶��" << endl;
		else
			cout << "ƽ���֣�" << sum / count << endl;
	}
	/************************************************************************/
	/*                      ѧ��������                                */
	/************************************************************************/
public:
	//�鿴�ɼ�
	void checkPersonageGrade()
	{
		for (int i = 0; i < grade.size(); ++i)
		{
			if (grade[i]._num == student[curStudentIndex]._num)
			{
				cout << "�ܳɼ���" << grade[i]._totalScore << endl;
				printf("�ߵ���ѧ�ɼ���%.f\n",grade[i]._score[0]);
				printf("������Ƴɼ���%.f\n", grade[i]._score[0]);
				printf("��ѧ����ɼ���%.f\n", grade[i]._score[0]);
			}
		}
		if (grade.empty())
			cout << "û�гɼ���" << endl;
	}
	//�޸ĸ�������
	void updatePassword()
	{
		string psw;
		cout << "����ԭ���룺";
		cin >> psw;
		if (psw == user[curUserIndex].password)
		{
			cout << "���������룺";
			cin >> user[curUserIndex].password;
		}
		else
			cout << "������󣬲����޸ģ�" << endl;
	}

	/************************************************************************/
	/*                       ���в���                     */
	/************************************************************************/
	//�޸�ѧ����Ϣ
	void updateStudentInfo(int num)
	{
		bool tag = false;
		for (int i = 0; i < student.size(); i++)
		{
			if (student[i]._num == num)
			{
				tag = true;
				cout << "�����޸ĵ�������";
				cin >> student[i]._name;
				cout << "�����޸ĵ�ѧ���Ա�";
				cin >> student[i]._sex;
				cout << "�����޸ĵ�ѧ����ϵ��ʽ��";
				cin >> student[i]._phoneNumber;
				cout << "�����޸ĵ�ѧ�����Һţ�";
				cin >> student[i]._dormitory;
				cout << "�޸���ɣ�" << endl;
				break;
			}
		}
		if (!tag)
			cout << "û�����ѧ����" << endl;
	}
	//�鿴ѧ��������Ϣ(ȫ�� �� ����)
	void checkPersonageInfo(int num)
	{
		Student stu;
		for (int i = 0; i < student.size(); ++i)
			if (student[i]._num == num)
			{
				stu = student[i];
				break;
			}

		cout << "*********************************************" << endl;
		cout << "ѧ�ţ�" << stu._num << endl;
		cout << "������" << stu._name << endl;
		cout << "�Ա�" << stu._sex << endl;
		cout << "��ϵ��ʽ��" << stu._phoneNumber << endl;
		cout << "���Һţ�" << stu._dormitory << endl;
	}

public:
	/*������Ϣ���ڱ���*/
	vector<Student> getStudent()
	{
		return student;
	}
	vector<Grade> getGrade()
	{
		return grade;
	}
public:
	void setStudent(vector<Student> s)
	{
		student = s;
	}
	void setGrade(vector<Grade> g)
	{
		grade = g;
	}
private:
	//ѧ������
	vector<Student> student;
	//�ɼ�����
	vector<Grade> grade;
};
/*
��¼��ʽ��Ϊ
����Ա ѧ�� ��ʦ����
�˺������ǽṹ���Ա������
*/
class file {
public:
	file() {}
	file(vector<Student> s, vector<Grade> g) :
		student(s), grade(g)
	{
	}
	vector<Student> getStudent()
	{
		return student;
	}
	vector<Grade> getGrade()
	{
		return grade;
	}

private:
	/*���ļ�*/
	bool openFile(string fileNmae, int way)
	{
		//д
		if (way == 0)
			fp.open(fileNmae, ios::out);
		//��
		if (way == 1)
			fp.open(fileNmae, ios::in);
		//����
		if (way == 2)
			fp.open(fileNmae, ios::app);

		if (!fp.is_open())
		{
			cout << "��ʧ��" << endl;
			return false;
		}
		return true;
	}
	/*�ر��ļ�*/
	void closeFile()
	{
		fp.close();
	}
public:
	/*���屣��*/
	void save()
	{
		saveStudent();
		saveGrade();
		saveUser();
	}

public:
	/*�����ȡ*/
	void read()
	{
		readStudent();
		readGrade();
		readUser();
	}
private:
	/*�����ļ�*/
	void saveStudent()
	{
		if (openFile("student.txt", 0))
		{
			for (int i = 0; i < student.size(); ++i)
			{
				fp << student[i]._dormitory << "\t"
					<< student[i]._name << "\t"
					<< student[i]._num << "\t"
					<< student[i]._phoneNumber << "\t"
					<< student[i]._sex;
				if (i + 1 != student.size())
					fp << "\n";
			}
		}
		closeFile();
	}
	void saveGrade()
	{
		if (openFile("grade.txt", 0))
		{
			for (int i = 0; i < grade.size(); ++i)
			{//����ѧ�� �༶ �ɼ� ��ѧ�� �ܳɼ� ƽ���ɼ�
				fp << grade[i]._avgScore << "\t"
					<< grade[i]._class << "\t"
					<< grade[i]._totalCredit << "\t"
					<< grade[i]._totalScore << "\t";
				for (int j = 0; j < grade[i]._credit.size(); ++j)
				{
					fp << grade[i]._credit[i] << "\t";
				}
				fp << -1 << "\t";
				for (int j = 0; j < grade[i]._score.size(); ++j)
				{
					fp << grade[i]._score[i] << "\t";
				}
				fp << -1;
				if (i + 1 != student.size())
					fp << "\n";
			}
		}
		closeFile();
	}
	void saveUser()
	{
		if (openFile("user.txt", 0))
		{
			for (int i = 0; i < user.size(); ++i)
			{
				fp << user[i].userName << "\t"
					<< user[i].password << "\t"
					<< user[i].num;
				if (i + 1 != user.size())
					fp << "\n";
			}
		}
		closeFile();
	}

private:
	/*��ȡ�ļ�*/
	void readStudent()
	{
		if (openFile("student.txt", 2))
		{
			closeFile();
			if (openFile("student.txt", 1))
			{
				while (fp.peek() != EOF)
				{
					Student stu;
					fp >> stu._dormitory >> stu._name >> stu._num
						>> stu._phoneNumber >> stu._sex;
					student.push_back(stu);
				}
			}
		}
		closeFile();
	}
	void readGrade()
	{
		if (openFile("grade.txt", 2))
		{
			closeFile();
			if (openFile("grade.txt", 1))
			{
				while (fp.peek() != EOF)
				{
					Grade g;
					fp >> g._avgScore >> g._class >> g._totalCredit >> g._totalScore;
					while (true)
					{
						int credit;
						fp >> credit;
						if (credit == -1)
							break;
						g._credit.push_back(credit);
					}
					while (true)
					{
						float score;
						fp >> score;
						if (score == -1)
							break;
						g._score.push_back(score);
					}
					grade.push_back(g);
				}
			}
		}
		closeFile();
	}
	void readUser()
	{
		if (openFile("user.txt", 2))
		{
			closeFile();
			if (openFile("user.txt", 1))
			{
				while (fp.peek() != EOF)
				{
					User stu;
					fp >> stu.userName >> stu.password >> stu.num;
					user.push_back(stu);
				}
			}
		}
		closeFile();
	}
private:
	fstream fp;
	vector<Student> student;
	vector<Grade> grade;
};

class Menu {
private:
	Operation op;

public:
	Menu()
	{
		file f;
		f.read();
		op.setGrade(f.getGrade());
		op.setStudent(f.getStudent());
	}
	//��֤����Ա����
	void adminPassword()
	{
		string root;
		cout << "����root���룺";
		cin >> root;
		if (root == ADMINPSW)
			adminMenu();
		else
			cout << "root�������" << endl;
	}
	//��֤��ʦ����
	void teacherPassword()
	{
		string teacherPsw;
		cout << "�����ʦ���룺";
		cin >> teacherPsw;
		if (teacherPsw == TEACHERPSW)
			teacherMenu();
		else
			cout << "��ʦ�������" << endl;
	}
	/*���˵�*/
	void mainMenu()
	{
		while (true)
		{
			system("cls");
			int choice;
			cout << "<0>�˳�" << endl;
			cout << "<1>ѧ����¼" << endl;
			cout << "<2>ѧ��ע��" << endl;
			cout << "<3>��ʦ��¼" << endl;
			cout << "<4>����Ա��¼" << endl;
			cin >> choice;
			switch (choice)
			{
			case 0:
			{
				file f(op.getStudent(), op.getGrade());
				f.save();
				return;
			}
			case 1:
				validatePasswordMenu();
				break;
			case 2:
				studentRegisterMenu();
				break;
			case 3:
				teacherPassword();
				break;
			case 4:
				adminPassword();
				break;
			default:cout << "�������!" << endl;
				break;
			}
			system("pause");
		}
	}

	/*ѧ���˵�*/
	void studentMenu()
	{
		vector<Student> temp(op.getStudent());
		//ѧ������1.�鿴������Ϣ2.�޸ĸ�����Ϣ3.�޸�����4.�鿴�ɼ�
		while (true)
		{
			system("cls");
			int choice;
			cout << "<0>�˳�" << endl;
			cout << "<1>�鿴������Ϣ" << endl;
			cout << "<2>�޸ĸ�����Ϣ" << endl;
			cout << "<3>�޸�����" << endl;
			cout << "<4>�鿴�ɼ�" << endl;
			cin >> choice;
			switch (choice)
			{
			case 0:
				return;
			case 1:
				if (temp.empty())
					cout << "û����Ϣ" << endl;
				else
					op.checkPersonageInfo(temp[op.curStudentIndex]._num);
				break;
			case 2:
				if (temp.empty())
					cout << "û����Ϣ" << endl;
				else
					op.updateStudentInfo(temp[op.curStudentIndex]._num);
				break;
			case 3:
				op.updatePassword();
				break;
			case 4:
				if (temp.empty())
					cout << "û����Ϣ" << endl;
				else
					op.checkPersonageGrade();
				break;
			default:cout << "�������!" << endl;
				break;
			}
			system("pause");
		}
	}

	/*��ʦ�˵�*/
	void teacherMenu()
	{
		vector<Student> temp(op.getStudent());
		//��ʦ���� 1.¼��ѧ���ɼ�2.�鿴�༶ƽ����3.�鿴ȫ��ѧ����Ϣ"4.�鿴ѧ��������Ϣ
		while (true)
		{
			system("cls");
			int choice;
			cout << "<0>�˳�" << endl;
			cout << "<1>¼��ѧ���ɼ�" << endl;
			cout << "<2>�鿴�༶ƽ����" << endl;
			cout << "<3>�鿴ȫ��ѧ����Ϣ" << endl;
			cout << "<4>�鿴ѧ��������Ϣ" << endl;
			cout << "<5>���ɼ�����ѧ����Ϣ" << endl;
			cin >> choice;
			switch (choice)
			{
			case 0:
				return;
			case 1:
				op.addStudentScore();
				break;
			case 2:
				op.checkClassAvgScore();
				break;
			case 3:
				for (int i = 0; i < temp.size(); ++i)
					op.checkPersonageInfo(temp[i]._num);
				break;
			case 4:
			{
				int num;
				cout << "����ѧ����ţ�";
				cin >> num;
				for (int i = 0; i < temp.size(); ++i)
				{
					if (temp[i]._num == num)
						op.checkPersonageInfo(temp[i]._num);
				}
				break;
			}
			case 5:
				op.sortStudentInfo_totalScore();
			default:cout << "�������!" << endl;
				break;
			}
			system("pause");
		}

	}

	/*����Ա�˵�*/
	void adminMenu()
	{
		//����Ա 1��¼��ѧ����Ϣ    2����ѯѧ����Ϣ 3��ɾ��ѧ����Ϣ     4���޸�ѧ����Ϣ
		while (true)
		{
			vector<Student> temp(op.getStudent());
			system("cls");
			int choice;
			cout << "<0>�˳�" << endl;
			cout << "<1>¼��ѧ����Ϣ" << endl;
			cout << "<2>��ѯѧ����Ϣ" << endl;
			cout << "<3>ɾ��ѧ����Ϣ" << endl;
			cout << "<4>�޸�ѧ����Ϣ" << endl;
			cin >> choice;
			switch (choice)
			{
			case 0:
				return;
			case 1:
				op.addStudentInfo();
				break;
			case 2:
			{
				int num;
				cout << "����ѧ����ţ�";
				cin >> num;
				for (int i = 0; i < temp.size(); ++i)
				{
					if (temp[i]._num == num)
						op.checkPersonageInfo(temp[i]._num);
				}
				break;
			}
			case 3:
				op.deleteStudentInfo();
				break;
			case 4:
			{
				int num;
				cout << "����ѧ����ţ�";
				cin >> num;
				op.updateStudentInfo(num);
			}
			break;
			default:cout << "�������!" << endl;
				break;
			}
			system("pause");
		}
	}

	/*������֤�˵�*/
	void validatePasswordMenu()
	{
		if (user.empty())
			cout << "û���˺���Ϣ��" << endl;
		else
		{
			vector<Student> temp(op.getStudent());
			bool tag = false;
			string userNmae;
			string psw;
			cout << "�����û�����";
			cin >> userNmae;
			cout << "�������룺";
			cin >> psw;
			for (int i = 0; i < user.size(); ++i)
			{
				if (user[i].userName == userNmae && user[i].password == psw)
				{
					op.curUserIndex = i;
					for (int j = 0; j < temp.size(); ++j)
					{
						if (user[i].num == temp[j]._num)
							op.curStudentIndex = j;
					}
					studentMenu();
					tag = true;
					break;
				}
			}
			if (!tag)
				cout << "�˺����������޴��˺ţ�" << endl;
		}
	}
	/*ѧ��ע��˵�*/
	void studentRegisterMenu()
	{
		User u;
		string psw;
		if (op.getStudent().empty())
			cout << "�������ѧ����Ϣ��" << endl;
		else
		{
			vector<Student> s(op.getStudent());
			int num;
			bool tag = false;
			cout << "����ѧ����ţ�";
			cin >> num;
			for (int i = 0; i < s.size(); ++i)
			{
				if (s[i]._num == num)
				{
					tag = true;
					cout << "�����û�����";
					cin >> u.userName;
					cout << "�������룺";
					cin >> psw;
					cout << "ȷ�����룺";
					cin >> u.password;
					if (psw == u.password)
					{
						u.num = s[i]._num;
						user.push_back(u);
						cout << "ע��ɹ���" << endl;
					}
					else
						cout << "�������벻һ��,ע��ʧ�ܣ�" << endl;
					break;
				}
				cout << "û�����ѧ����ע��ʧ�ܣ�" << endl;
			}
		}
	}
};
int main()
{
	Menu menu;
	menu.mainMenu();
	system("pause");
	return 0;
}