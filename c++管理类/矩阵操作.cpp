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
#include <string>
#include <fstream>
#include <vector>
using namespace std;

enum Type{READ,WRITE};

class MatrixOperations{
public:
	void inputMatrix(vector<vector<int> > &ans)
	{
		int i,j;
		int row, column;
		cout << "输入矩阵的行列数：";
		cin >> row >> column;
		ans.resize(column);
		for (i = 0; i < column; ++i)
		{
			vector<int> temp(row, 0);
			ans[i] = temp;
		}

		for (i = 0; i < column; ++i)
			for (j = 0; j < row; ++j)
				cin >> ans[i][j];
		cout << "****************************" << endl;
	}

public:
	void print(vector<vector<int> > ans)
	{
		for (int i = 0; i < ans.size(); ++i)
		{
			for (int j = 0; j < ans[0].size(); ++j)
				cout << ans[i][j] << "\t";
			cout << endl;
		}
	}

public:
	//检验是否满足加减
	bool is_addAndSub()
	{
		if (matrixA.empty() || matrixB.empty())
			return false;
	
		return matrixA[0].size() == matrixB[0].size()
			&& matrixA.size() == matrixB.size();
	}
	//矩阵加减
	void matrixAddAndSub(int type)
	{
		int i,j;
		if (!is_addAndSub())
		{
			cout << "矩阵不符合加减法" << endl;
			return;
		}
		
		vector<vector<int> > ans;
		for (i = 0; i < matrixA.size(); ++i)
		{
			vector<int> temp;
			for (j = 0; j < matrixA[0].size(); ++j)
			{
				if(type == 0)
					temp.push_back(matrixA[i][j] + matrixB[i][j]);
				if(type == 1)
					temp.push_back(matrixA[i][j] - matrixB[i][j]);
			}
			ans.push_back(temp);
		}

		if (type == 0)
			cout << "matrixA + matrixB 结果为：" << endl;
		if(type == 1)
			cout<< "matrixA - matrixB 结果为：" << endl;
		print(ans);
	}

public:
	//判断是否符合相乘
	bool is_Ride()
	{
		if (matrixA.empty() || matrixB.empty())
			return false;
		//行列相等
		return matrixA[0].size() == matrixB.size();
	}
	void ride()
	{
		int n;
		cout << "输入一个数：";
		cin >> n;
		matrixRideNumber(matrixA, 0, n);
		matrixRideNumber(matrixB, 1, n);
	}
	//矩阵和数相乘
	void matrixRideNumber(vector<vector<int> > matrix, int type, int n)
	{
		if (!matrix.empty())
		{
			for (int i = 0; i < matrix.size(); ++i)
				for (int j = 0; j < matrix[0].size(); ++j)
				{
					matrix[i][j] *= n;
				}
			if (type == 0)
				cout << "matrixA  *   " << n << "结果为：" << endl;
			if(type == 1)
				cout << "matrixB *   " << n << "结果为：" << endl;
			print(matrix);
		}
	}
	//矩阵矩阵相乘
	void matrixRideMatrix()
	{
		int i,j,k;
		if (!is_Ride())
			cout << "矩阵不满足相乘！" << endl;

		vector<vector<int> > ans;
		for (i = 0; i < matrixA[0].size(); ++i)
		{
			vector<int> temp;
			for (k = 0; k < matrixB[0].size(); ++k)
			{
				int sum = 0;
				for (j = 0; j < matrixB.size(); ++j)
				{
					sum += matrixA[i][j] * matrixB[j][k];
				}
				temp.push_back(sum);
			}
			ans.push_back(temp);
		}
		cout << "matrixA * matrixB 结果为：" << endl;
		print(ans);
	}

public:
	void transposition()
	{
		matrixTransposition(matrixA, 0);
		matrixTransposition(matrixB, 1);
	}
	//矩阵转置
	void matrixTransposition(vector<vector<int> > matrix,int type)
	{
		int i,j;
		if (matrix.empty())
		{
			cout << "矩阵为空，无法转置！" << endl;
			return;
		}

		vector<vector<int> > ans;
		ans.resize(matrix[0].size());
		for (i = 0; i < ans.size(); ++i)
		{
			vector<int> temp;
			temp.resize(matrix.size());
			ans[i] = temp;
		}

		for (i = 0; i < matrix.size(); ++i)
		{
			for (j = 0; j < matrix[0].size(); ++j)
			{
				ans[j][i] = matrix[i][j];
			}
		}
		if (type == 0)
			cout << "matrixA矩阵转置后：" << endl;
		if(type == 1)
			cout << "matrixB矩阵转置后：" << endl;
		print(ans);
	}

public:
	//打开文件
	bool openFile(string fileName,Type type)
	{
		if (type == READ)
			file.open(fileName.c_str(), ios::in);
		if (type == WRITE)
			file.open(fileName.c_str(), ios::out);
		return file.is_open();
	}
	//关闭文件
	void closeFile()
	{
		file.close();
	}
	//矩阵存储
	void saveMatrix(string fileName,vector<vector<int> > ans,char ch)
	{
		int i,j; 
		if (!openFile(fileName,WRITE))
		{
			cout << "文件打开失败！" << endl;
			return;
		}

		file << ch << endl;
		for (i = 0; i < ans.size(); ++i)
		{
			for (j = 0; j < ans[0].size(); ++j)
			{
				file << ans[i][j] << "\t";
			}
			file << LONG_MAX;
			if (i + 1 != ans.size())
				file <<"\n";
		}
		closeFile();
	}

	//矩阵读取
	void readMatrix(string fileName)
	{
		if (!openFile(fileName,READ))
		{
			cout << "没有"<<fileName << endl;
			return;
		}
		char ch;
		file >> ch;
		while (file.peek() != EOF)
		{
			vector<int> temp;
			while (true)
			{
				long num;
				file >> num;
				if (num == LONG_MAX)
					break;
				temp.push_back(num);
			}
			if (ch == 'A')
				matrixA.push_back(temp);
			if (ch == 'B')
				matrixB.push_back(temp);
		}
		closeFile();
	}
public:
	fstream file;
	//矩阵数组
	vector<vector<int> > matrixA;
	//矩阵数组二
	vector<vector<int> > matrixB;
};

void menu()
{
	int choice;
	MatrixOperations matrix;
	while (true)
	{
		system("cls");
		cout << "<0>退出矩阵运算" << endl;
		cout << "<1>用户输入矩阵" << endl;
		cout << "<2>文件读取矩阵" << endl;
		cout << "<3>矩阵加矩阵" << endl;
		cout << "<4>矩阵减矩阵" << endl;
		cout << "<5>矩阵乘数" << endl;
		cout << "<6>矩阵乘矩阵" << endl;
		cout << "<7>矩阵转置" << endl;
		cout << "选择操作：(0 - 7)：";
		cin >> choice;
		switch (choice)
		{
		case 0:
			matrix.saveMatrix("matrixA.txt",matrix.matrixA,'A');
			matrix.saveMatrix("matrixB.txt", matrix.matrixB, 'B');
			return;
		case 1:
			matrix.inputMatrix(matrix.matrixA);
			matrix.inputMatrix(matrix.matrixB);
			break;
		case 2:
			matrix.readMatrix("matrixA.txt");
			matrix.readMatrix("matrixB.txt");
			break;
		case 3:
			matrix.matrixAddAndSub(0);
			break;
		case 4:
			matrix.matrixAddAndSub(1);
			break;
		case 5:
			matrix.ride();
			break;
		case 6:
			matrix.matrixRideMatrix();
			break;
		case 7:
			matrix.transposition();
			break;
		default:cout << "输入错误！" << endl;
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