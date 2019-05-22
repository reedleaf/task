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
		cout << "����������������";
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
	//�����Ƿ�����Ӽ�
	bool is_addAndSub()
	{
		if (matrixA.empty() || matrixB.empty())
			return false;
	
		return matrixA[0].size() == matrixB[0].size()
			&& matrixA.size() == matrixB.size();
	}
	//����Ӽ�
	void matrixAddAndSub(int type)
	{
		int i,j;
		if (!is_addAndSub())
		{
			cout << "���󲻷��ϼӼ���" << endl;
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
			cout << "matrixA + matrixB ���Ϊ��" << endl;
		if(type == 1)
			cout<< "matrixA - matrixB ���Ϊ��" << endl;
		print(ans);
	}

public:
	//�ж��Ƿ�������
	bool is_Ride()
	{
		if (matrixA.empty() || matrixB.empty())
			return false;
		//�������
		return matrixA[0].size() == matrixB.size();
	}
	void ride()
	{
		int n;
		cout << "����һ������";
		cin >> n;
		matrixRideNumber(matrixA, 0, n);
		matrixRideNumber(matrixB, 1, n);
	}
	//����������
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
				cout << "matrixA  *   " << n << "���Ϊ��" << endl;
			if(type == 1)
				cout << "matrixB *   " << n << "���Ϊ��" << endl;
			print(matrix);
		}
	}
	//����������
	void matrixRideMatrix()
	{
		int i,j,k;
		if (!is_Ride())
			cout << "����������ˣ�" << endl;

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
		cout << "matrixA * matrixB ���Ϊ��" << endl;
		print(ans);
	}

public:
	void transposition()
	{
		matrixTransposition(matrixA, 0);
		matrixTransposition(matrixB, 1);
	}
	//����ת��
	void matrixTransposition(vector<vector<int> > matrix,int type)
	{
		int i,j;
		if (matrix.empty())
		{
			cout << "����Ϊ�գ��޷�ת�ã�" << endl;
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
			cout << "matrixA����ת�ú�" << endl;
		if(type == 1)
			cout << "matrixB����ת�ú�" << endl;
		print(ans);
	}

public:
	//���ļ�
	bool openFile(string fileName,Type type)
	{
		if (type == READ)
			file.open(fileName.c_str(), ios::in);
		if (type == WRITE)
			file.open(fileName.c_str(), ios::out);
		return file.is_open();
	}
	//�ر��ļ�
	void closeFile()
	{
		file.close();
	}
	//����洢
	void saveMatrix(string fileName,vector<vector<int> > ans,char ch)
	{
		int i,j; 
		if (!openFile(fileName,WRITE))
		{
			cout << "�ļ���ʧ�ܣ�" << endl;
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

	//�����ȡ
	void readMatrix(string fileName)
	{
		if (!openFile(fileName,READ))
		{
			cout << "û��"<<fileName << endl;
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
	//��������
	vector<vector<int> > matrixA;
	//���������
	vector<vector<int> > matrixB;
};

void menu()
{
	int choice;
	MatrixOperations matrix;
	while (true)
	{
		system("cls");
		cout << "<0>�˳���������" << endl;
		cout << "<1>�û��������" << endl;
		cout << "<2>�ļ���ȡ����" << endl;
		cout << "<3>����Ӿ���" << endl;
		cout << "<4>���������" << endl;
		cout << "<5>�������" << endl;
		cout << "<6>����˾���" << endl;
		cout << "<7>����ת��" << endl;
		cout << "ѡ�������(0 - 7)��";
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
		default:cout << "�������" << endl;
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