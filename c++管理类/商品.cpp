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
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

class Goods {
public:
	virtual ~Goods() {}
	virtual void display() {}
	friend istream& operator >>(istream& in, Goods* g)
	{
		in >> g->id >> g->name >> g->number >> g->price;
		return in;
	}
	friend ostream& operator <<(ostream& out, Goods* g)
	{
		cout << "代号" << "\t" << "商品名称" << "\t"
			<< "数量" << "\t" << "价格" << "\t"
			<< "类别" << endl;
		out << g->id << "\t" << g->name << "\t\t"
			<< g->number << "\t" << g->price << "\t"
			<< g->type;
		return out;
	}
public:
	int id;				//编号
	string name;	//商品名称
	int number;	//数量
	int price;		//单价
	string type;	//类型
};

class HouseApp : virtual public Goods {
public:
	virtual ~HouseApp() {}
	virtual void display() 
	{
		cout << "家用电器信息：" << endl;
	}
};
class Daily : virtual public Goods {
public:
	virtual ~Daily() {}
	virtual void display() 
	{
		cout << "日用品信息：" << endl;
	}
};

class Management :public HouseApp , public Daily{
public:
	virtual void display()
	{
		for (int i = 0; i < management.size(); ++i)
		{
			management[i]->display();
			cout << management[i] << endl;
		}
	}
	//添加记录
	void input()
	{
		int n;
		while (true)
		{
			Goods *goods;
			cout << "选择商品类型：(1:家电 2:日用品)";
			cin >> n;
			if (n == 1)
			{
				goods = new HouseApp;
				goods->type = "家用电器";
			}
			else
			{
				goods = new Daily;
				goods->type = "日用品";
			}

			cout << "商品代号" << "\t" << "商品名称" << "\t"
				<< "数量" << "\t" << "价格" << endl;
			cin >> goods;
			management.push_back(goods);

			cout << "是否继续添加？(0:否  1:是)：";
			cin >> n;
			if (n == 0)
				break;
		}
	}
	//查询id
	vector<Goods*>::iterator find_id()
	{
		int _id;
		cout << "输入操作商品的代号：";
		cin >> _id;
		return ::find_if(management.begin(), management.end(),
			[&_id](Goods* g) {return g->id == _id; });
	}
	//修改商品数量
	void updateGoodsNumber()
	{
		vector<Goods*>::iterator it;
		it = find_id();
		if (it != management.end())
		{
			cout << "数量：" << (*it)->number;
			cout << "输入新的数量：";
			cin >> (*it)->number;
			cout << "修改成功！" << endl;
		}
		else
			cout << "没有改商品,修改失败！" << endl;
	}
	//浏览商品信息
	void showGoodInfo()
	{
		display();
	}
	//按商品代号查找
	void idQuery()
	{
		vector<Goods*>::iterator it;
		it = find_id();
		if (it != management.end())
		{
			(*it)->display();
			cout << *it << endl;
		}
		else
			cout << "没有该商品!" << endl;
	}
	//删除一条记录
	void delInfo()
	{
		vector<Goods*>::iterator it;
		it = find_id();
		if (it != management.end())
		{
			management.erase(it);
			cout << "删除成功！" << endl;
		}
		else
			cout << "删除失败,没有该商品！" << endl; 
	}
public:
	void load()
	{
		fstream in("Goods.txt");
		if (!in.is_open())
		{
			cout << "文件不存在！" << endl;
			system("pause");
			return;
		}

		while (in.peek() != EOF)
		{
			Goods* goods;
			string _type;
			in >> _type;
			if (_type == "家用电器")
				goods = new HouseApp;
			else
				goods = new Daily;
			goods->type = _type;
			in >> goods->name >> goods->number >> goods->price >> goods->id;
			management.push_back(goods);
		}
		in.close();
	}
	void save()
	{
		fstream out;
		out.open("Goods.txt", ios::out);
		if (!out.is_open())
		{
			cout << "文件打开失败" << endl;
			return;
		}
		for (int i = 0; i < management.size(); ++i)
		{
			out << management[i]->type<< "\t"
				<< management[i]->name << "\t"
				<< management[i]->number << "\t"
				<< management[i]->price << "\t"
				<< management[i]->id;
			if (i != management.size() - 1)
				out << "\n";
		}
		out.close();
	}
public:
	~Management()
	{
		for (int i = 0; i < management.size(); ++i)
			delete management[i];
	}
private:
	vector<Goods*> management;
};

void menu()
{
	Management m;
	m.load();
	while (true)
	{
		int choice;
		system("cls");
		cout << "***商品仓库管理系统***" << endl;
		cout << "【0】退出系统" << endl;
		cout << "【1】添加记录" << endl;
		cout << "【2】修改商品数量" << endl;
		cout << "【3】浏览商品信息" << endl;
		cout << "【4】按商品代号查询" << endl;
		cout << "【5】删除记录" << endl;
		cout << "输入选择(0 - 5)：";
		cin >> choice;
		switch (choice)
		{
		case 0:m.save();
			return;
		case 1:m.input();
			break;
		case 2:m.updateGoodsNumber();
			break;
		case 3:m.showGoodInfo();
			break;
		case 4:m.idQuery();
			break;
		case 5:m.delInfo();
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