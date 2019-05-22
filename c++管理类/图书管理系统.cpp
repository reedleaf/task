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
.课题　：　图书管理系统 
.概述　：　见题目描述
.要求　：　见题目描述
*/

/*
1、问题描述
定义图书类，属性有：书名、出版社、ISBN号、作者、库存量、价格等信息和相关的对属性做操作的行为。
主要完成对图书的销售、统计和图书的简单管理。
2、功能要求
（1）销售功能。购买书籍时，输入相应的ISBN号，并在书库中查找该书的相关信息。如果有库存量，输入购买的册数，进行相应计算。如果库存量不够，给出提示信息，结束购买。
（2）图书简单管理功能。
添加功能：主要完成图书信息的添加，要求ISBN号唯一。当添加了重复的编号时，则提示数据添加重复并取消添加。
查询功能：可按书名、ISBN号、作者、出版社进行查询。若存在相应信息，输出所查询的信息，若不存在该记录，则提示“该标题不存在！”。
修改功能：可根据查询结果对相应的记录进行修改，修改时注意ISBN号的唯一性。
删除功能：主要完成图书信息的删除。输入要删除的ISBN号，根据编号删除该物品的记录，如果该编号不在物品库中，则提示“该编号不存在”。
（3）统计功能。
输出当前书库中所有图书的总数及详细信息；可按书的价格、库存量、作者、出版社进行统计，输出统计信息时，要按从大到小进行排序。
（7）图书存盘：将当前程序中的图书信息存入文件中。
（8）读出信息：从文件中将图书信息读入程序。

*/
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

/*图书结构体*/
typedef struct _tBookInfo {
	char isbn[128];			/*ISBN*/
	char name[256];			/*书名*/
	char author[256];		/*作者*/
	char press[256];		/*出版单位*/
	char time[256];			/*出版时间*/
	double price;			/*价格*/
	int stock;				/*库存*/
	struct _tBookInfo* next;	/*下一个节点*/
} BookInfo, *pBookInfo;

/*图书管理系统*/
class BooksManager {
public:
	BooksManager() :head(NULL) {

	}

	virtual ~BooksManager() {

	}

public:
	void run() {
		/*从文件中加载图书数据*/
		pBookInfo head = loadBookInfoFile();
		/*进入系统*/
		menu(&head);
		/*清理图书列表*/
		clearBookInfoList(head);
	}

private:
	/*清空输入缓冲区*/
	void emptyStdin() {
		int c;
		while ((c = getchar()) != '\n' && c != EOF);
	}

	/*等待按下任意键*/
	void waitingPressAnyKey() {
		emptyStdin();
		getchar();
	}

	/*清屏*/
	void clearScreen() {
		system("cls");
	}

	/*添加图书节点，返回链表首节点指针*/
	pBookInfo addBookInfoNode(pBookInfo head, pBookInfo node) {
		if (head) {
			pBookInfo cursor = head;
			while (cursor->next) {
				cursor = cursor->next;
			}
			/*将新节点插入到链表尾部*/
			cursor->next = node;
			return head;
		}
		else {
			/*链表为空返回该节点*/
			return node;
		}
	}

	/*删除图书节点，返回链表首节点指针*/
	pBookInfo removeBookInfoNode(pBookInfo head, pBookInfo node) {
		if (head) {
			if (head == node) {
				/*删除节点为首节点*/
				head = node->next;
				/*删除该节点*/
				free(node);
			}
			else {
				pBookInfo cursor = head;
				while (cursor->next) {
					/*找到要删除节点的上一个节点*/
					if (cursor->next == node) {
						/*将上一个节点指向删除节点的下一个节点*/
						cursor->next = node->next;
						/*删除该节点*/
						free(node);
						break;
					}
					cursor = cursor->next;
				}
			}
		}
		return head;
	}

	/*通过ISBN查找图书节点*/
	pBookInfo findBookInfoNodeByISBN(pBookInfo head, char* isbn) {
		pBookInfo cursor = head;
		while (cursor) {
			/*匹配图书*/
			if (strcmp(cursor->isbn, isbn) == 0) {
				return cursor;
			}
			cursor = cursor->next;
		}
		return NULL;
	}

	/*通过书名查找图书节点*/
	pBookInfo findBookInfoNodeByName(pBookInfo head, char* name) {
		pBookInfo cursor = head;
		while (cursor) {
			/*匹配图书*/
			if (strcmp(cursor->name, name) == 0) {
				return cursor;
			}
			cursor = cursor->next;
		}
		return NULL;
	}

	/*通过出版单位查找图书节点*/
	pBookInfo findBookInfoNodeByPress(pBookInfo head, char* press) {
		pBookInfo cursor = head;
		while (cursor) {
			/*匹配图书*/
			if (strcmp(cursor->press, press) == 0) {
				return cursor;
			}
			cursor = cursor->next;
		}
		return NULL;
	}

	/*通过库存查找图书节点*/
	pBookInfo findBookInfoNodeByStock(pBookInfo head, int min, int max) {
		pBookInfo cursor = head;
		while (cursor) {
			/*匹配图书*/
			if (cursor->stock >= min && cursor->stock <= max) {
				return cursor;
			}
			cursor = cursor->next;
		}
		return NULL;
	}

	/*交换两个图书节点*/
	void swapBookInfoNode(pBookInfo lhs, pBookInfo rhs) {
		pBookInfo temp = (pBookInfo)malloc(sizeof(BookInfo));
		/*计算除next之外要交换的字节数*/
		int size = ((char*)&temp->next) - ((char*)temp);
		memcpy(temp, lhs, size);
		memcpy(lhs, rhs, size);
		memcpy(rhs, temp, size);
		free(temp);
	}

	/*通过ISBN排序*/
	void sortBookInfoNodeByISBN(pBookInfo head) {
		pBookInfo index = head;
		while (index) {
			pBookInfo target = index;
			pBookInfo cursor = target->next;
			while (cursor) {
				/*比较模式*/
				if (strcmp(target->isbn, cursor->isbn) > 0) {
					target = cursor;
				}
				cursor = cursor->next;
			}

			/*交换数据*/
			if (target != index) {
				swapBookInfoNode(target, index);
			}
			index = index->next;
		}
	}

	/*通过书名排序*/
	void sortBookInfoNodeByName(pBookInfo head) {
		pBookInfo index = head;
		while (index) {
			pBookInfo target = index;
			pBookInfo cursor = target->next;
			while (cursor) {
				/*比较模式*/
				if (strcmp(target->name, cursor->name) > 0) {
					target = cursor;
				}
				cursor = cursor->next;
			}

			/*交换数据*/
			if (target != index) {
				swapBookInfoNode(target, index);
			}
			index = index->next;
		}
	}

	/*通过出版社排序*/
	void sortBookInfoNodeByPress(pBookInfo head) {
		pBookInfo index = head;
		while (index) {
			pBookInfo target = index;
			pBookInfo cursor = target->next;
			while (cursor) {
				/*比较模式*/
				if (strcmp(target->press, cursor->press) > 0) {
					target = cursor;
				}
				cursor = cursor->next;
			}

			/*交换数据*/
			if (target != index) {
				swapBookInfoNode(target, index);
			}
			index = index->next;
		}
	}

	/*通过价格排序*/
	void sortBookInfoNodeByPrice(pBookInfo head) {
		pBookInfo index = head;
		while (index) {
			pBookInfo target = index;
			pBookInfo cursor = target->next;
			while (cursor) {
				/*比较模式*/
				if (target->price < cursor->price) {
					target = cursor;
				}
				cursor = cursor->next;
			}

			/*交换数据*/
			if (target != index) {
				swapBookInfoNode(target, index);
			}
			index = index->next;
		}
	}

	/*计算图书节点数*/
	int countBookInfoNode(pBookInfo head) {
		pBookInfo cursor = head;
		int count = 0;
		while (cursor) {
			++count;
			cursor = cursor->next;
		}
		return count;
	}

	/*将图书信息存储到文件*/
	/*c方式文件读写比较方便*/
	void saveBookInfoFile(const pBookInfo head) {
		pBookInfo cursor = head;
		FILE* file = fopen("bookinfo.dat", "wb");
		if (file) {
			int count = countBookInfoNode(head);
			/*将用户节点总数写入文件起始位置*/
			fwrite(&count, sizeof(int), 1, file);
			while (cursor) {
				fwrite(cursor, sizeof(BookInfo), 1, file);
				cursor = cursor->next;
			}
			fclose(file);
		}
		else {
			cout<<"写文件失败！"<<endl;
		}
	}

	/*从文件中加载用户信息*/
	pBookInfo loadBookInfoFile() {
		pBookInfo head = NULL;
		FILE* file = fopen("bookinfo.dat", "rb");
		if (file) {
			int count = 0;
			/*读取文件起始位置的节点总数*/
			fread(&count, sizeof(int), 1, file);
			while (count--) {
				pBookInfo book = (pBookInfo)malloc(sizeof(BookInfo));
				memset(book, 0, sizeof(BookInfo));
				fread(book, sizeof(BookInfo), 1, file);
				/*将指向下个节点的指针重置成NULL*/
				book->next = NULL;
				head = addBookInfoNode(head, book);
			}
			fclose(file);
		}
		else {
			cout << "读文件失败！" << endl;
		}
		return head;
	}

	/*清理图书列表，回收内存*/
	void clearBookInfoList(pBookInfo head) {
		while (head) {
			head = removeBookInfoNode(head, head);
		}
	}

	/*显示图书信息*/
	void showBook(pBookInfo book) {
		cout<<"┌-------------------------------------------------┐\n";
		cout<<"    ISBN：";
		cout<< book->isbn<<endl;
		cout << "    书名：";
		cout <<  book->name << endl;
		cout << "    作者：";
		cout <<  book->author << endl;
		cout << "    出版单位：";
		cout << book->press << endl;
		cout << "    出版时间：";
		cout <<  book->time << endl;
		cout << "    价格：";
		cout <<  book->price << endl;
		cout << "    库存：";
		cout<< book->stock << endl;
		cout<<"└-------------------------------------------------┘\n";
	}

	/*编辑图书信息*/
	void editBook(pBookInfo book) {
		cout<<"            #录入图书信息#\n";
		cout << "┌-------------------------------------------------┐\n";
		cout << "    ISBN：";
		if (strlen(book->isbn)) {
			cout << "%s\n", book->isbn;
		}
		else {
			cin>>book->isbn;
		}
		cout << "    书名：";
		cin>> book->name;
		cout << "    作者：";
		cin >> book->author;
		cout << "    出版单位：";
		cin >> book->press;
		cout << "    出版时间：";
		cin >> book->time;
		cout << "    价格：";
		cin >> book->price;
		cout << "└-------------------------------------------------┘\n";
	}

	/*显示图书清单选项*/
	void showBookListOption(pBookInfo head) {
		int option = 1;
		while (1) {
			pBookInfo cursor = head;
			clearScreen();
			while (cursor) {
				showBook(cursor);
				cursor = cursor->next;
			}
			cout << "\n【1 按ISBN排序 2 按书名排序 | 3 按出版社排序 | 4 按价格排序 | 0 返回】\n";
			cin >> option;
			switch (option) {
			case 1:
				sortBookInfoNodeByISBN(head);
				break;
			case 2:
				sortBookInfoNodeByName(head);
				break;
			case 3:
				sortBookInfoNodeByPress(head);
				break;
			case 4:
				sortBookInfoNodeByPrice(head);
				break;
			case 0:
				return;
			}
		}
	}

	/*添加图书选项*/
	void createBookOption(pBookInfo* head) {
		pBookInfo book = (pBookInfo)malloc(sizeof(BookInfo));
		memset(book, 0U, sizeof(BookInfo));
		clearScreen();
		editBook(book);
		if (findBookInfoNodeByISBN(*head, book->isbn)) {
			free(book);
			cout << "\n图书添加失败，存在相同图书的ISBN编码！\n";
		}
		else {
			*head = addBookInfoNode(*head, book);
			/*同步文件信息*/
			saveBookInfoFile(*head);
			cout << "\n图书添加成功！\n";
		}
		waitingPressAnyKey();
	}

	/*修改图书选项*/
	void updateBookOption(pBookInfo head) {
		char isbn[128] = { 0 };
		pBookInfo target = NULL;
		clearScreen();
		cout << "        ┌------------------------┐\n";
		cout << "               #修改图书#\n";
		cout << "             ISBN：";
		cin >> isbn;
		cout << "        └------------------------┘\n";
		target = findBookInfoNodeByISBN(head, isbn);
		if (target) {
			showBook(target);
			editBook(target);
			/*同步文件信息*/
			saveBookInfoFile(head);
			cout << "\n图书修改成功！\n";
		}
		else {
			cout << "\n未找到该图书！\n";
		}
		waitingPressAnyKey();
	}

	/*删除图书选项*/
	void removeBookOption(pBookInfo* head) {
		char isbn[128] = { 0 };
		pBookInfo target = NULL;
		clearScreen();
		cout << "        ┌------------------------┐\n";
		cout << "               #删除图书#\n";
		cout << "             ISBN：";
		cin >> isbn;
		cout << "        └------------------------┘\n";
		target = findBookInfoNodeByISBN(*head, isbn);
		if (target) {
			showBook(target);
			*head = removeBookInfoNode(*head, target);
			/*同步文件信息*/
			saveBookInfoFile(*head);
			cout << "\n图书删除成功！\n";
		}
		else {
			cout << "\n未找到该图书！\n";
		}
		waitingPressAnyKey();
	}

	/*按ISBN查询图书选项*/
	void searchBookByIDOption(pBookInfo head) {
		char isbn[128] = { 0 };
		pBookInfo target = NULL;
		clearScreen();
		cout << "        ┌------------------------┐\n";
		cout << "               #按ISBN查询#\n";
		cout << "             ISBN：";
		scanf("%s", isbn);
		cout << "        └------------------------┘\n";
		target = findBookInfoNodeByISBN(head, isbn);
		if (target) {
			showBook(target);
		}
		else {
			cout << "\n未找到该图书！\n";
		}
		waitingPressAnyKey();
	}

	/*按书名查询图书选项*/
	void searchBookByNameOption(pBookInfo head) {
		char name[128] = { 0 };
		pBookInfo target = NULL;
		clearScreen();
		cout << "        ┌------------------------┐\n";
		cout << "               #按书名查询#\n";
		cout << "             书名：";
		cin >> name;
		cout << "        └------------------------┘\n";
		target = findBookInfoNodeByName(head, name);
		if (target) {
			do {
				showBook(target);
				target = findBookInfoNodeByName(target->next, name);
			} while (target);
		}
		else {
			cout << "\n未找到该图书！\n";
		}
		waitingPressAnyKey();
	}

	/*按出版单位查询图书选项*/
	void searchBookByPressOption(pBookInfo head) {
		char press[128] = { 0 };
		pBookInfo target = NULL;
		clearScreen();
		cout << "        ┌------------------------┐\n";
		cout << "               #按出版单位查询#\n";
		cout << "             书名：";
		cin >> press;
		cout << "        └------------------------┘\n";
		target = findBookInfoNodeByPress(head, press);
		if (target) {
			do {
				showBook(target);
				target = findBookInfoNodeByPress(target->next, press);
			} while (target);
		}
		else {
			cout << "\n未找到该图书！\n";
		}
		waitingPressAnyKey();
	}

	/*按库存查询图书选项*/
	void searchBookByStockOption(pBookInfo head) {
		int min, max;
		pBookInfo target = NULL;
		clearScreen();
		cout << "        ┌------------------------┐\n";
		cout << "               #按库存查询#\n";
		cout << "             库存量大于等于：";
		cin >> min;
		cout << "             库存量小于等于：";
		cin >> max;
		cout << "        └------------------------┘\n";
		target = findBookInfoNodeByStock(head, min, max);
		if (target) {
			do {
				showBook(target);
				target = findBookInfoNodeByStock(target->next, min, max);
			} while (target);
		}
		else {
			cout << "\n未找到该图书！\n";
		}
		waitingPressAnyKey();
	}

	/*图书浏览菜单*/
	void browseBooksOption(pBookInfo head) {
		int option;
		while (1) {
			clearScreen();
			cout << "        ┌-------------------------------┐\n";
			cout << "                 #图书浏览#\n";
			cout << "\n";
			cout << "              【1】 图书清单\n";
			cout << "              【2】 按ISBN查询\n";
			cout << "              【3】 按书名查询\n";
			cout << "              【4】 按出版单位查询\n";
			cout << "              【5】 按库存量查询\n";
			cout << "              【0】 返回\n";
			cout << "\n";
			cout << "        └-------------------------------┘\n";
			cout << "\n";
			scanf("%d", &option);
			switch (option) {
			case 1:
				showBookListOption(head);
				break;
			case 2:
				searchBookByIDOption(head);
				break;
			case 3:
				searchBookByNameOption(head);
				break;
			case 4:
				searchBookByPressOption(head);
				break;
			case 5:
				searchBookByStockOption(head);
				break;
			case 0:
				return;
			}
		}
	}

	/*图书管理菜单*/
	void manageBooksOption(pBookInfo* head) {
		int option;
		while (1) {
			clearScreen();
			cout << "        ┌-------------------------------┐\n";
			cout << "                 #图书管理#\n";
			cout << "\n";
			cout << "              【1】 添加图书\n";
			cout << "              【2】 修改图书\n";
			cout << "              【3】 删除图书\n";
			cout << "              【0】 返回\n";
			cout << "\n";
			cout << "        └-------------------------------┘\n";
			cout << "\n";
			cin >> option;
			switch (option) {
			case 1:
				createBookOption(head);
				break;
			case 2:
				updateBookOption(*head);
				break;
			case 3:
				removeBookOption(head);
				break;
			case 0:
				return;
			}
		}
	}

	/*采购*/
	void inputStock(pBookInfo head) {
		char isbn[128] = { 0 };
		pBookInfo target = NULL;
		clearScreen();
		cout << "        ┌------------------------┐\n";
		cout << "               #采购#\n";
		cout << "             ISBN：";
		cin >> isbn;
		cout << "        └------------------------┘\n";
		target = findBookInfoNodeByISBN(head, isbn);
		if (target) {
			int number;
			showBook(target);
			cout << "        ┌------------------------┐\n";
			cout << "             采购数量：";
			scanf("%d", &number);
			cout << "       └------------------------┘\n";
			if (number > 0) {
				target->stock += number;
				/*同步文件信息*/
				saveBookInfoFile(head);
				cout << "\n操作成功！\n";
			}
			else {
				cout << "\n库存更新失败，采购数量应该大于0！\n";
			}
		}
		else {
			cout << "\n未找到该图书！\n";
		}
		waitingPressAnyKey();
	}

	/*出售*/
	void outputStock(pBookInfo head) {
		char isbn[128] = { 0 };
		pBookInfo target = NULL;
		clearScreen();
		cout << "        ┌------------------------┐\n";
		cout << "               #出售#\n";
		cout << "             ISBN：";
		cin >> isbn;
		cout << "        └------------------------┘\n";
		target = findBookInfoNodeByISBN(head, isbn);
		if (target) {
			int number;
			showBook(target);
			cout << "        ┌------------------------┐\n";
			cout << "             出售数量：";
			cin >>number;
			cout << "        └------------------------┘\n";
			if (target->stock - number >= 0) {
				target->stock -= number;
				/*同步文件信息*/
				saveBookInfoFile(head);
				cout << "\n操作成功！\n";
			}
			else {
				cout << "\n库存更新失败，没有足够的库存！\n";
			}
		}
		else {
			cout << "\n未找到该图书！\n";
		}
		waitingPressAnyKey();
	}

	/*主菜单*/
	void menu(pBookInfo* head) {
		while (1) {
			int option;
			clearScreen();
			cout << "        ┌-------------------------------┐\n";
			cout << "               #图书管理系统#\n";
			cout << "\n";
			cout << "              【1】 浏览图书\n";
			cout << "              【2】 图书管理\n";
			cout << "              【3】 采购\n";
			cout << "              【4】 出售\n";
			cout << "              【0】 退出系统\n";
			cout << "\n";
			cout << "        └-------------------------------┘\n";
			cout << "\n";
			cin >> option;
			switch (option) {
			case 1:
				browseBooksOption(*head);
				break;
			case 2:
				manageBooksOption(head);
				break;
			case 3:
				inputStock(*head);
				break;
			case 4:
				outputStock(*head);
				break;
			case 0:
				return;
			}
		}
	}

private:
	pBookInfo head;
};

int main() {
	BooksManager manager;
	manager.run();
	return 0;
}