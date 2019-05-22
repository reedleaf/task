/*
################################
.      原创代写，诚信可靠；
.      注释详细，编码工整；
.      水平一流，讲解易懂；
.      遵循教材，绝不超纲。
.          < ReedLeaf >
.        QQ : 1020273485
.  https://codefox.taobao.com
################################

.语言　：　C++
.课题　：　作业管理系统 
.概述　：　见题目描述
.要求　：　见题目描述

注明:
	《1》我们是按照客户给出的详细要求去编写的,收费是按照当时的要求合理收费的。所以后期要求添加功能我们是不做的,

	《2》 拿到程序后尽快测试，并提出问题,由于我们工作量很大,不会一直长时间服务，
	         发生过用户一个月后半夜让我们修改的事情(请问她这一个月都在干嘛呢？)所以望能谅解

	《3》我们不包括教会这个程序,小问题可以问我们,定当解答不过有些客户会把代写和辅导混为一谈,到头来我们得到的还是一个差评，
	         所以请认真阅读。
*/
/* 
题目 10：课程作业管理系统 
要求： 
1、学生可以将课程作业或实验报告等作业类型（以 WORD、TXT 文件形式为例），支持文
件的增加、修改、删除、查询； 
2、教师可以对作业进行评分，并支持对学生提交作业进行查询等操作； 
3、具有查看面板。 

*/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

//初始教师密码
#define ADMINPASSWORD "123456"

//学生类
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
	string _name;				//名字
	string _homework;		//作业
	float _score;					//成绩
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

//操作类
class Operator {
public:
	//查找学生
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

			cout << "姓名：";
			cin >> name;
			s.setName(name);

			cout << "作业：";
			cin >> homework;
			s.setHomework(homework);

			student.push_back(s);
			cout << "是否继续：（0:否  1:是）";
			cin >> choice;
			if (!choice)
				break;
		}
	}
	//del
	void delStudentInfo()
	{
		string name;
		cout << "输入学生姓名：";
		cin >> name;
		auto it = findInfo(name);
		if (it != student.end()) 
		{
			student.erase(it);
			cout << "删除成功！" << endl;
		}
		else
			cout << "没有该学生！" << endl;
	}
	//update
	void updateStudentInfo()
	{
		string name;
		cout << "输入学生姓名：";
		cin >> name;
		auto it = findInfo(name);
		if (it != student.end())
		{
			string homework;
			cout << "输入新作业：";
			cin >> homework;
			it->setHomework(homework);
			cout << "修改完成！" << endl;
		}
		else
			cout << "没有这个学生！" << endl;
	}
	//query
	void queryStudentInfo()
	{
		string name;
		cout << "输入学生姓名：";
		cin >> name;
		auto it = findInfo(name);
		if (it != student.end())
		{
			cout << "姓名：" << it->getName() << endl;
			cout << "作业：" << it->getHomework() << endl;
			if (it->getScore() == -1)
				cout << "成绩：未评" << endl;
			else
				cout << "成绩：" << it->getScore()<<endl;
		}
	}

public:
	/*teacherOperator*/
	void teacherSetSCore()
	{
		for (int i = 0; i < student.size(); ++i)
		{
			float score;
			cout << student[i].getName() << "的" << student[i].getHomework() << endl;
			cout << "请打分：";
			cin >> score;
			student[i].setScore(score);
		}
		if (student.empty())
			cout << "没有学生上交作业！" << endl;
	}

public:
	//save
	void save()
	{
		fstream outfile;
		outfile.open("homework.txt", ios::out);
		if (!outfile.is_open())
		{
			cout << "文件打开失败！" << endl;
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
		cout << "*****学生界面******" << endl;
		cout << "<0>退出学生界面" << endl;
		cout << "<1>添加作业" << endl;
		cout << "<2>删除作业" << endl;
		cout << "<3>修改作业" << endl;
		cout << "<4>查询作业" << endl;
		cout << "选择(0-4)：";
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
		default:cout << "输入错误！" << endl;
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
		cout << "*****教师界面******" << endl;
		cout << "<0>退出教师界面" << endl;
		cout << "<1>添加作业" << endl;
		cout << "<2>删除作业" << endl;
		cout << "<3>修改作业" << endl;
		cout << "<4>查询作业" << endl;
		cout << "<5>作业评分" << endl;
		cout << "选择(0-4)：";
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
		default:cout << "输入错误！" << endl;
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
		cout << "<0>退出系统" << endl;
		cout << "<1>学生界面" << endl;
		cout << "<2>教师界面" << endl;
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
			//教师登录要输入密码
			string password;
			cout << "输入密码：";
			cin >> password;
			if (password == ADMINPASSWORD)
				teacherMenu();
			else
				cout << "密码错误！" << endl;
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
