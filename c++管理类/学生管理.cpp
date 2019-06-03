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
#include <iostream>
#include <vector>
#include <fstream>
#include<string>
#include <algorithm>

using namespace std;

#define ADMINPSW "admin"				//管理员密码
#define TEACHERPSW "teacher"		//老师密码

struct User
{
	string userName;
	string password;
	int num;								//学生用户添加学号和其他信息关联
};
vector<User> user;			//用户数组
/*学生类
包含 姓名 学号 性别 联系方式 寝室号
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

成绩类
包含学分 班级 成绩 总学分 总成绩 平均成绩
*/
class Grade {
public:
	Grade() {}
	~Grade() {}

public:
	int _num;			//学号外键
	vector<int> _credit;
	vector<float> _score;
	float _avgScore;
	int _totalCredit;
	float _totalScore;
	string _class;
};

/************************************************************************/
/*                          操作类                             */
/************************************************************************/
class Operation
{
public:
	int curStudentIndex;
	int curUserIndex;
public:
	Operation() {}
	~Operation() {}

	//管理员信息工作区
public:
	//录入学生信息
	void addStudentInfo()
	{
		while (true)
		{
			//包含 姓名 学号 性别 联系方式 寝室号
			char choice;
			Student stu;

			cout << "输入学生姓名：";
			cin >> stu._name;
			cout << "输入学生学号：";
			cin >> stu._num;
			cout << "输入学生性别：";
			cin >> stu._sex;
			cout << "输入学生联系方式：";
			cin >> stu._phoneNumber;
			cout << "输入学生寝室号：";
			cin >> stu._dormitory;

			student.push_back(stu);
			cout << "是否继续？(n:否  y:是)：";
			cin >> choice;
			cin.clear();
			cin.sync();
			if (choice == 'N' || choice == 'n')
				break;
		}
	}
	//删除学生信息
	void deleteStudentInfo()
	{
		int num;
		bool tag = false;
		cout << "输入学生编号：";
		cin >> num;

		//相当于遍历数组
		for (vector<Student>::iterator it = student.begin(); it != student.end(); ++it)
		{
			if (it->_num == num)
			{
				student.erase(it);//删除数组里面一个元素
				tag = true;				//有这个学生,表示找到了
				break;
			}
		}
		if (!tag)
			cout << "没有这个学生！" << endl;
	}
	//排序学生信息（按总成绩）
	void sortStudentInfo_totalScore()
	{
		if (grade.empty())
		{
			cout << "请输入成绩！" << endl;
			return;
		}
		vector<Grade> temp(grade);
		vector<Student> tempStu(student);
		//排序函数(冒泡排序)
		for (int i = 0; i < temp.size() - 1; ++i)
		{
			for (int j = 0; j < temp.size() - 1 - i; ++j)
			{
				if (temp[j]._totalScore > temp[j + 1]._totalScore)
					swap(temp[j], temp[j + 1]);//交换两个元素
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
		cout << "排序完成！" << endl;
	}

	/************************************************************************/
	/*                       教师工作区                               */
	/************************************************************************/
public:
	//录入学生成绩
	void addStudentScore()
	{
		if (student.empty())
			cout << "没有学生！" << endl;
		//循环信息vecot按编号录入
		for (int i = 0; i < student.size(); ++i)
		{
			cout << "*************************************" << endl;
			cout << "学生" << i + 1 << endl;
			int choice;
			float _score;
			Grade temp;
			temp._totalCredit = 0;
			temp._totalScore = 0;
			temp._num = student[i]._num;
			cout << "输入班级：";
			cin >> temp._class;
			cout << "输入学生高等数学成绩：";
			cin >> _score;
			temp._score.push_back(_score);
			temp._totalScore += _score;
			cout << "输入学生程序设计成绩：";
			cin >> _score;
			temp._score.push_back(_score);
			temp._totalScore += _score;
			cout << "输入学生大学物理成绩：";
			cin >> _score;
			temp._score.push_back(_score);
			temp._totalScore += _score;
			while (true)
			{
				float _credit;
				cout << "输入学生各种学分：";
				cin >> _credit;
				temp._credit.push_back(_credit);
				temp._totalCredit += _credit;
				cout << "按0退出输入，1继续：";
				cin >> choice;
				if (choice == 0)
					break;
			}
			temp._avgScore = temp._totalScore / temp._score.size();
			grade.push_back(temp);
		}
	}
	//查看班级平均分
	void checkClassAvgScore()
	{
		bool tag = false;
		float sum = 0;
		int count = 0;
		string _class;
		cout << "输入班级：" << endl;
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
			cout << "没有班级！" << endl;
		else
			cout << "平均分：" << sum / count << endl;
	}
	/************************************************************************/
	/*                      学生工作区                                */
	/************************************************************************/
public:
	//查看成绩
	void checkPersonageGrade()
	{
		for (int i = 0; i < grade.size(); ++i)
		{
			if (grade[i]._num == student[curStudentIndex]._num)
			{
				cout << "总成绩：" << grade[i]._totalScore << endl;
				printf("高等数学成绩：%.f\n",grade[i]._score[0]);
				printf("程序设计成绩：%.f\n", grade[i]._score[0]);
				printf("大学物理成绩：%.f\n", grade[i]._score[0]);
			}
		}
		if (grade.empty())
			cout << "没有成绩：" << endl;
	}
	//修改个人密码
	void updatePassword()
	{
		string psw;
		cout << "输入原密码：";
		cin >> psw;
		if (psw == user[curUserIndex].password)
		{
			cout << "输入新密码：";
			cin >> user[curUserIndex].password;
		}
		else
			cout << "密码错误，不能修改！" << endl;
	}

	/************************************************************************/
	/*                       公有操作                     */
	/************************************************************************/
	//修改学生信息
	void updateStudentInfo(int num)
	{
		bool tag = false;
		for (int i = 0; i < student.size(); i++)
		{
			if (student[i]._num == num)
			{
				tag = true;
				cout << "输入修改的姓名：";
				cin >> student[i]._name;
				cout << "输入修改的学生性别：";
				cin >> student[i]._sex;
				cout << "输入修改的学生联系方式：";
				cin >> student[i]._phoneNumber;
				cout << "输入修改的学生寝室号：";
				cin >> student[i]._dormitory;
				cout << "修改完成！" << endl;
				break;
			}
		}
		if (!tag)
			cout << "没有这个学生！" << endl;
	}
	//查看学生个人信息(全部 或 个人)
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
		cout << "学号：" << stu._num << endl;
		cout << "姓名：" << stu._name << endl;
		cout << "性别：" << stu._sex << endl;
		cout << "联系方式：" << stu._phoneNumber << endl;
		cout << "寝室号：" << stu._dormitory << endl;
	}

public:
	/*返回信息用于保存*/
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
	//学生数组
	vector<Student> student;
	//成绩数组
	vector<Grade> grade;
};
/*
登录方式分为
管理员 学生 教师三种
账号密码是结构体成员变量；
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
	/*打开文件*/
	bool openFile(string fileNmae, int way)
	{
		//写
		if (way == 0)
			fp.open(fileNmae, ios::out);
		//读
		if (way == 1)
			fp.open(fileNmae, ios::in);
		//附加
		if (way == 2)
			fp.open(fileNmae, ios::app);

		if (!fp.is_open())
		{
			cout << "打开失败" << endl;
			return false;
		}
		return true;
	}
	/*关闭文件*/
	void closeFile()
	{
		fp.close();
	}
public:
	/*集体保存*/
	void save()
	{
		saveStudent();
		saveGrade();
		saveUser();
	}

public:
	/*集体读取*/
	void read()
	{
		readStudent();
		readGrade();
		readUser();
	}
private:
	/*保存文件*/
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
			{//包含学分 班级 成绩 总学分 总成绩 平均成绩
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
	/*读取文件*/
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
	//验证管理员密码
	void adminPassword()
	{
		string root;
		cout << "输入root密码：";
		cin >> root;
		if (root == ADMINPSW)
			adminMenu();
		else
			cout << "root密码错误！" << endl;
	}
	//验证教师密码
	void teacherPassword()
	{
		string teacherPsw;
		cout << "输入教师密码：";
		cin >> teacherPsw;
		if (teacherPsw == TEACHERPSW)
			teacherMenu();
		else
			cout << "教师密码错误！" << endl;
	}
	/*主菜单*/
	void mainMenu()
	{
		while (true)
		{
			system("cls");
			int choice;
			cout << "<0>退出" << endl;
			cout << "<1>学生登录" << endl;
			cout << "<2>学生注册" << endl;
			cout << "<3>教师登录" << endl;
			cout << "<4>管理员登录" << endl;
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
			default:cout << "输入错误!" << endl;
				break;
			}
			system("pause");
		}
	}

	/*学生菜单*/
	void studentMenu()
	{
		vector<Student> temp(op.getStudent());
		//学生可以1.查看个人信息2.修改个人信息3.修改密码4.查看成绩
		while (true)
		{
			system("cls");
			int choice;
			cout << "<0>退出" << endl;
			cout << "<1>查看个人信息" << endl;
			cout << "<2>修改个人信息" << endl;
			cout << "<3>修改密码" << endl;
			cout << "<4>查看成绩" << endl;
			cin >> choice;
			switch (choice)
			{
			case 0:
				return;
			case 1:
				if (temp.empty())
					cout << "没有信息" << endl;
				else
					op.checkPersonageInfo(temp[op.curStudentIndex]._num);
				break;
			case 2:
				if (temp.empty())
					cout << "没有信息" << endl;
				else
					op.updateStudentInfo(temp[op.curStudentIndex]._num);
				break;
			case 3:
				op.updatePassword();
				break;
			case 4:
				if (temp.empty())
					cout << "没有信息" << endl;
				else
					op.checkPersonageGrade();
				break;
			default:cout << "输入错误!" << endl;
				break;
			}
			system("pause");
		}
	}

	/*教师菜单*/
	void teacherMenu()
	{
		vector<Student> temp(op.getStudent());
		//老师可以 1.录入学生成绩2.查看班级平均分3.查看全部学生信息"4.查看学生个人信息
		while (true)
		{
			system("cls");
			int choice;
			cout << "<0>退出" << endl;
			cout << "<1>录入学生成绩" << endl;
			cout << "<2>查看班级平均分" << endl;
			cout << "<3>查看全部学生信息" << endl;
			cout << "<4>查看学生个人信息" << endl;
			cout << "<5>按成绩排序学生信息" << endl;
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
				cout << "输入学生编号：";
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
			default:cout << "输入错误!" << endl;
				break;
			}
			system("pause");
		}

	}

	/*管理员菜单*/
	void adminMenu()
	{
		//管理员 1、录入学生信息    2、查询学生信息 3、删除学生信息     4、修改学生信息
		while (true)
		{
			vector<Student> temp(op.getStudent());
			system("cls");
			int choice;
			cout << "<0>退出" << endl;
			cout << "<1>录入学生信息" << endl;
			cout << "<2>查询学生信息" << endl;
			cout << "<3>删除学生信息" << endl;
			cout << "<4>修改学生信息" << endl;
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
				cout << "输入学生编号：";
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
				cout << "输入学生编号：";
				cin >> num;
				op.updateStudentInfo(num);
			}
			break;
			default:cout << "输入错误!" << endl;
				break;
			}
			system("pause");
		}
	}

	/*密码验证菜单*/
	void validatePasswordMenu()
	{
		if (user.empty())
			cout << "没有账号信息！" << endl;
		else
		{
			vector<Student> temp(op.getStudent());
			bool tag = false;
			string userNmae;
			string psw;
			cout << "输入用户名：";
			cin >> userNmae;
			cout << "输入密码：";
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
				cout << "账号密码错误或无此账号！" << endl;
		}
	}
	/*学生注册菜单*/
	void studentRegisterMenu()
	{
		User u;
		string psw;
		if (op.getStudent().empty())
			cout << "请先添加学生信息！" << endl;
		else
		{
			vector<Student> s(op.getStudent());
			int num;
			bool tag = false;
			cout << "输入学生编号：";
			cin >> num;
			for (int i = 0; i < s.size(); ++i)
			{
				if (s[i]._num == num)
				{
					tag = true;
					cout << "输入用户名：";
					cin >> u.userName;
					cout << "输入密码：";
					cin >> psw;
					cout << "确认密码：";
					cin >> u.password;
					if (psw == u.password)
					{
						u.num = s[i]._num;
						user.push_back(u);
						cout << "注册成功！" << endl;
					}
					else
						cout << "两次密码不一致,注册失败！" << endl;
					break;
				}
				cout << "没有这个学生，注册失败！" << endl;
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