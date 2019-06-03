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
		cout << "����" << "\t" << "��Ʒ����" << "\t"
			<< "����" << "\t" << "�۸�" << "\t"
			<< "���" << endl;
		out << g->id << "\t" << g->name << "\t\t"
			<< g->number << "\t" << g->price << "\t"
			<< g->type;
		return out;
	}
public:
	int id;				//���
	string name;	//��Ʒ����
	int number;	//����
	int price;		//����
	string type;	//����
};

class HouseApp : virtual public Goods {
public:
	virtual ~HouseApp() {}
	virtual void display() 
	{
		cout << "���õ�����Ϣ��" << endl;
	}
};
class Daily : virtual public Goods {
public:
	virtual ~Daily() {}
	virtual void display() 
	{
		cout << "����Ʒ��Ϣ��" << endl;
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
	//��Ӽ�¼
	void input()
	{
		int n;
		while (true)
		{
			Goods *goods;
			cout << "ѡ����Ʒ���ͣ�(1:�ҵ� 2:����Ʒ)";
			cin >> n;
			if (n == 1)
			{
				goods = new HouseApp;
				goods->type = "���õ���";
			}
			else
			{
				goods = new Daily;
				goods->type = "����Ʒ";
			}

			cout << "��Ʒ����" << "\t" << "��Ʒ����" << "\t"
				<< "����" << "\t" << "�۸�" << endl;
			cin >> goods;
			management.push_back(goods);

			cout << "�Ƿ������ӣ�(0:��  1:��)��";
			cin >> n;
			if (n == 0)
				break;
		}
	}
	//��ѯid
	vector<Goods*>::iterator find_id()
	{
		int _id;
		cout << "���������Ʒ�Ĵ��ţ�";
		cin >> _id;
		return ::find_if(management.begin(), management.end(),
			[&_id](Goods* g) {return g->id == _id; });
	}
	//�޸���Ʒ����
	void updateGoodsNumber()
	{
		vector<Goods*>::iterator it;
		it = find_id();
		if (it != management.end())
		{
			cout << "������" << (*it)->number;
			cout << "�����µ�������";
			cin >> (*it)->number;
			cout << "�޸ĳɹ���" << endl;
		}
		else
			cout << "û�и���Ʒ,�޸�ʧ�ܣ�" << endl;
	}
	//�����Ʒ��Ϣ
	void showGoodInfo()
	{
		display();
	}
	//����Ʒ���Ų���
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
			cout << "û�и���Ʒ!" << endl;
	}
	//ɾ��һ����¼
	void delInfo()
	{
		vector<Goods*>::iterator it;
		it = find_id();
		if (it != management.end())
		{
			management.erase(it);
			cout << "ɾ���ɹ���" << endl;
		}
		else
			cout << "ɾ��ʧ��,û�и���Ʒ��" << endl; 
	}
public:
	void load()
	{
		fstream in("Goods.txt");
		if (!in.is_open())
		{
			cout << "�ļ������ڣ�" << endl;
			system("pause");
			return;
		}

		while (in.peek() != EOF)
		{
			Goods* goods;
			string _type;
			in >> _type;
			if (_type == "���õ���")
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
			cout << "�ļ���ʧ��" << endl;
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
		cout << "***��Ʒ�ֿ����ϵͳ***" << endl;
		cout << "��0���˳�ϵͳ" << endl;
		cout << "��1����Ӽ�¼" << endl;
		cout << "��2���޸���Ʒ����" << endl;
		cout << "��3�������Ʒ��Ϣ" << endl;
		cout << "��4������Ʒ���Ų�ѯ" << endl;
		cout << "��5��ɾ����¼" << endl;
		cout << "����ѡ��(0 - 5)��";
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