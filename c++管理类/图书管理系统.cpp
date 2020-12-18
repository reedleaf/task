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
.���⡡����ͼ�����ϵͳ 
.��������������Ŀ����
.Ҫ�󡡣�������Ŀ����
*/

/*
1����������
����ͼ���࣬�����У������������硢ISBN�š����ߡ���������۸����Ϣ����صĶ���������������Ϊ��
��Ҫ��ɶ�ͼ������ۡ�ͳ�ƺ�ͼ��ļ򵥹���
2������Ҫ��
��1�����۹��ܡ������鼮ʱ��������Ӧ��ISBN�ţ���������в��Ҹ���������Ϣ������п���������빺��Ĳ�����������Ӧ���㡣��������������������ʾ��Ϣ����������
��2��ͼ��򵥹����ܡ�
��ӹ��ܣ���Ҫ���ͼ����Ϣ����ӣ�Ҫ��ISBN��Ψһ����������ظ��ı��ʱ������ʾ��������ظ���ȡ����ӡ�
��ѯ���ܣ��ɰ�������ISBN�š����ߡ���������в�ѯ����������Ӧ��Ϣ���������ѯ����Ϣ���������ڸü�¼������ʾ���ñ��ⲻ���ڣ�����
�޸Ĺ��ܣ��ɸ��ݲ�ѯ�������Ӧ�ļ�¼�����޸ģ��޸�ʱע��ISBN�ŵ�Ψһ�ԡ�
ɾ�����ܣ���Ҫ���ͼ����Ϣ��ɾ��������Ҫɾ����ISBN�ţ����ݱ��ɾ������Ʒ�ļ�¼������ñ�Ų�����Ʒ���У�����ʾ���ñ�Ų����ڡ���
��3��ͳ�ƹ��ܡ�
�����ǰ���������ͼ�����������ϸ��Ϣ���ɰ���ļ۸񡢿���������ߡ����������ͳ�ƣ����ͳ����Ϣʱ��Ҫ���Ӵ�С��������
��7��ͼ����̣�����ǰ�����е�ͼ����Ϣ�����ļ��С�
��8��������Ϣ�����ļ��н�ͼ����Ϣ�������

*/
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

/*ͼ��ṹ��*/
typedef struct _tBookInfo {
	char isbn[128];			/*ISBN*/
	char name[256];			/*����*/
	char author[256];		/*����*/
	char press[256];		/*���浥λ*/
	char time[256];			/*����ʱ��*/
	double price;			/*�۸�*/
	int stock;				/*���*/
	struct _tBookInfo* next;	/*��һ���ڵ�*/
} BookInfo, *pBookInfo;

/*ͼ�����ϵͳ*/
class BooksManager {
public:
	BooksManager() :head(NULL) {

	}

	virtual ~BooksManager() {

	}

public:
	void run() {
		/*���ļ��м���ͼ������*/
		pBookInfo head = loadBookInfoFile();
		/*����ϵͳ*/
		menu(&head);
		/*����ͼ���б�*/
		clearBookInfoList(head);
	}

private:
	/*������뻺����*/
	void emptyStdin() {
		int c;
		while ((c = getchar()) != '\n' && c != EOF);
	}

	/*�ȴ����������*/
	void waitingPressAnyKey() {
		emptyStdin();
		getchar();
	}

	/*����*/
	void clearScreen() {
		system("cls");
	}

	/*���ͼ��ڵ㣬���������׽ڵ�ָ��*/
	pBookInfo addBookInfoNode(pBookInfo head, pBookInfo node) {
		if (head) {
			pBookInfo cursor = head;
			while (cursor->next) {
				cursor = cursor->next;
			}
			/*���½ڵ���뵽����β��*/
			cursor->next = node;
			return head;
		}
		else {
			/*����Ϊ�շ��ظýڵ�*/
			return node;
		}
	}

	/*ɾ��ͼ��ڵ㣬���������׽ڵ�ָ��*/
	pBookInfo removeBookInfoNode(pBookInfo head, pBookInfo node) {
		if (head) {
			if (head == node) {
				/*ɾ���ڵ�Ϊ�׽ڵ�*/
				head = node->next;
				/*ɾ���ýڵ�*/
				free(node);
			}
			else {
				pBookInfo cursor = head;
				while (cursor->next) {
					/*�ҵ�Ҫɾ���ڵ����һ���ڵ�*/
					if (cursor->next == node) {
						/*����һ���ڵ�ָ��ɾ���ڵ����һ���ڵ�*/
						cursor->next = node->next;
						/*ɾ���ýڵ�*/
						free(node);
						break;
					}
					cursor = cursor->next;
				}
			}
		}
		return head;
	}

	/*ͨ��ISBN����ͼ��ڵ�*/
	pBookInfo findBookInfoNodeByISBN(pBookInfo head, char* isbn) {
		pBookInfo cursor = head;
		while (cursor) {
			/*ƥ��ͼ��*/
			if (strcmp(cursor->isbn, isbn) == 0) {
				return cursor;
			}
			cursor = cursor->next;
		}
		return NULL;
	}

	/*ͨ����������ͼ��ڵ�*/
	pBookInfo findBookInfoNodeByName(pBookInfo head, char* name) {
		pBookInfo cursor = head;
		while (cursor) {
			/*ƥ��ͼ��*/
			if (strcmp(cursor->name, name) == 0) {
				return cursor;
			}
			cursor = cursor->next;
		}
		return NULL;
	}

	/*ͨ�����浥λ����ͼ��ڵ�*/
	pBookInfo findBookInfoNodeByPress(pBookInfo head, char* press) {
		pBookInfo cursor = head;
		while (cursor) {
			/*ƥ��ͼ��*/
			if (strcmp(cursor->press, press) == 0) {
				return cursor;
			}
			cursor = cursor->next;
		}
		return NULL;
	}

	/*ͨ��������ͼ��ڵ�*/
	pBookInfo findBookInfoNodeByStock(pBookInfo head, int min, int max) {
		pBookInfo cursor = head;
		while (cursor) {
			/*ƥ��ͼ��*/
			if (cursor->stock >= min && cursor->stock <= max) {
				return cursor;
			}
			cursor = cursor->next;
		}
		return NULL;
	}

	/*��������ͼ��ڵ�*/
	void swapBookInfoNode(pBookInfo lhs, pBookInfo rhs) {
		pBookInfo temp = (pBookInfo)malloc(sizeof(BookInfo));
		/*�����next֮��Ҫ�������ֽ���*/
		int size = ((char*)&temp->next) - ((char*)temp);
		memcpy(temp, lhs, size);
		memcpy(lhs, rhs, size);
		memcpy(rhs, temp, size);
		free(temp);
	}

	/*ͨ��ISBN����*/
	void sortBookInfoNodeByISBN(pBookInfo head) {
		pBookInfo index = head;
		while (index) {
			pBookInfo target = index;
			pBookInfo cursor = target->next;
			while (cursor) {
				/*�Ƚ�ģʽ*/
				if (strcmp(target->isbn, cursor->isbn) > 0) {
					target = cursor;
				}
				cursor = cursor->next;
			}

			/*��������*/
			if (target != index) {
				swapBookInfoNode(target, index);
			}
			index = index->next;
		}
	}

	/*ͨ����������*/
	void sortBookInfoNodeByName(pBookInfo head) {
		pBookInfo index = head;
		while (index) {
			pBookInfo target = index;
			pBookInfo cursor = target->next;
			while (cursor) {
				/*�Ƚ�ģʽ*/
				if (strcmp(target->name, cursor->name) > 0) {
					target = cursor;
				}
				cursor = cursor->next;
			}

			/*��������*/
			if (target != index) {
				swapBookInfoNode(target, index);
			}
			index = index->next;
		}
	}

	/*ͨ������������*/
	void sortBookInfoNodeByPress(pBookInfo head) {
		pBookInfo index = head;
		while (index) {
			pBookInfo target = index;
			pBookInfo cursor = target->next;
			while (cursor) {
				/*�Ƚ�ģʽ*/
				if (strcmp(target->press, cursor->press) > 0) {
					target = cursor;
				}
				cursor = cursor->next;
			}

			/*��������*/
			if (target != index) {
				swapBookInfoNode(target, index);
			}
			index = index->next;
		}
	}

	/*ͨ���۸�����*/
	void sortBookInfoNodeByPrice(pBookInfo head) {
		pBookInfo index = head;
		while (index) {
			pBookInfo target = index;
			pBookInfo cursor = target->next;
			while (cursor) {
				/*�Ƚ�ģʽ*/
				if (target->price < cursor->price) {
					target = cursor;
				}
				cursor = cursor->next;
			}

			/*��������*/
			if (target != index) {
				swapBookInfoNode(target, index);
			}
			index = index->next;
		}
	}

	/*����ͼ��ڵ���*/
	int countBookInfoNode(pBookInfo head) {
		pBookInfo cursor = head;
		int count = 0;
		while (cursor) {
			++count;
			cursor = cursor->next;
		}
		return count;
	}

	/*��ͼ����Ϣ�洢���ļ�*/
	/*c��ʽ�ļ���д�ȽϷ���*/
	void saveBookInfoFile(const pBookInfo head) {
		pBookInfo cursor = head;
		FILE* file = fopen("bookinfo.dat", "wb");
		if (file) {
			int count = countBookInfoNode(head);
			/*���û��ڵ�����д���ļ���ʼλ��*/
			fwrite(&count, sizeof(int), 1, file);
			while (cursor) {
				fwrite(cursor, sizeof(BookInfo), 1, file);
				cursor = cursor->next;
			}
			fclose(file);
		}
		else {
			cout<<"д�ļ�ʧ�ܣ�"<<endl;
		}
	}

	/*���ļ��м����û���Ϣ*/
	pBookInfo loadBookInfoFile() {
		pBookInfo head = NULL;
		FILE* file = fopen("bookinfo.dat", "rb");
		if (file) {
			int count = 0;
			/*��ȡ�ļ���ʼλ�õĽڵ�����*/
			fread(&count, sizeof(int), 1, file);
			while (count--) {
				pBookInfo book = (pBookInfo)malloc(sizeof(BookInfo));
				memset(book, 0, sizeof(BookInfo));
				fread(book, sizeof(BookInfo), 1, file);
				/*��ָ���¸��ڵ��ָ�����ó�NULL*/
				book->next = NULL;
				head = addBookInfoNode(head, book);
			}
			fclose(file);
		}
		else {
			cout << "���ļ�ʧ�ܣ�" << endl;
		}
		return head;
	}

	/*����ͼ���б������ڴ�*/
	void clearBookInfoList(pBookInfo head) {
		while (head) {
			head = removeBookInfoNode(head, head);
		}
	}

	/*��ʾͼ����Ϣ*/
	void showBook(pBookInfo book) {
		cout<<"��-------------------------------------------------��\n";
		cout<<"    ISBN��";
		cout<< book->isbn<<endl;
		cout << "    ������";
		cout <<  book->name << endl;
		cout << "    ���ߣ�";
		cout <<  book->author << endl;
		cout << "    ���浥λ��";
		cout << book->press << endl;
		cout << "    ����ʱ�䣺";
		cout <<  book->time << endl;
		cout << "    �۸�";
		cout <<  book->price << endl;
		cout << "    ��棺";
		cout<< book->stock << endl;
		cout<<"��-------------------------------------------------��\n";
	}

	/*�༭ͼ����Ϣ*/
	void editBook(pBookInfo book) {
		cout<<"            #¼��ͼ����Ϣ#\n";
		cout << "��-------------------------------------------------��\n";
		cout << "    ISBN��";
		if (strlen(book->isbn)) {
			cout << "%s\n", book->isbn;
		}
		else {
			cin>>book->isbn;
		}
		cout << "    ������";
		cin>> book->name;
		cout << "    ���ߣ�";
		cin >> book->author;
		cout << "    ���浥λ��";
		cin >> book->press;
		cout << "    ����ʱ�䣺";
		cin >> book->time;
		cout << "    �۸�";
		cin >> book->price;
		cout << "��-------------------------------------------------��\n";
	}

	/*��ʾͼ���嵥ѡ��*/
	void showBookListOption(pBookInfo head) {
		int option = 1;
		while (1) {
			pBookInfo cursor = head;
			clearScreen();
			while (cursor) {
				showBook(cursor);
				cursor = cursor->next;
			}
			cout << "\n��1 ��ISBN���� 2 ���������� | 3 ������������ | 4 ���۸����� | 0 ���ء�\n";
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

	/*���ͼ��ѡ��*/
	void createBookOption(pBookInfo* head) {
		pBookInfo book = (pBookInfo)malloc(sizeof(BookInfo));
		memset(book, 0U, sizeof(BookInfo));
		clearScreen();
		editBook(book);
		if (findBookInfoNodeByISBN(*head, book->isbn)) {
			free(book);
			cout << "\nͼ�����ʧ�ܣ�������ͬͼ���ISBN���룡\n";
		}
		else {
			*head = addBookInfoNode(*head, book);
			/*ͬ���ļ���Ϣ*/
			saveBookInfoFile(*head);
			cout << "\nͼ����ӳɹ���\n";
		}
		waitingPressAnyKey();
	}

	/*�޸�ͼ��ѡ��*/
	void updateBookOption(pBookInfo head) {
		char isbn[128] = { 0 };
		pBookInfo target = NULL;
		clearScreen();
		cout << "        ��------------------------��\n";
		cout << "               #�޸�ͼ��#\n";
		cout << "             ISBN��";
		cin >> isbn;
		cout << "        ��------------------------��\n";
		target = findBookInfoNodeByISBN(head, isbn);
		if (target) {
			showBook(target);
			editBook(target);
			/*ͬ���ļ���Ϣ*/
			saveBookInfoFile(head);
			cout << "\nͼ���޸ĳɹ���\n";
		}
		else {
			cout << "\nδ�ҵ���ͼ�飡\n";
		}
		waitingPressAnyKey();
	}

	/*ɾ��ͼ��ѡ��*/
	void removeBookOption(pBookInfo* head) {
		char isbn[128] = { 0 };
		pBookInfo target = NULL;
		clearScreen();
		cout << "        ��------------------------��\n";
		cout << "               #ɾ��ͼ��#\n";
		cout << "             ISBN��";
		cin >> isbn;
		cout << "        ��------------------------��\n";
		target = findBookInfoNodeByISBN(*head, isbn);
		if (target) {
			showBook(target);
			*head = removeBookInfoNode(*head, target);
			/*ͬ���ļ���Ϣ*/
			saveBookInfoFile(*head);
			cout << "\nͼ��ɾ���ɹ���\n";
		}
		else {
			cout << "\nδ�ҵ���ͼ�飡\n";
		}
		waitingPressAnyKey();
	}

	/*��ISBN��ѯͼ��ѡ��*/
	void searchBookByIDOption(pBookInfo head) {
		char isbn[128] = { 0 };
		pBookInfo target = NULL;
		clearScreen();
		cout << "        ��------------------------��\n";
		cout << "               #��ISBN��ѯ#\n";
		cout << "             ISBN��";
		scanf("%s", isbn);
		cout << "        ��------------------------��\n";
		target = findBookInfoNodeByISBN(head, isbn);
		if (target) {
			showBook(target);
		}
		else {
			cout << "\nδ�ҵ���ͼ�飡\n";
		}
		waitingPressAnyKey();
	}

	/*��������ѯͼ��ѡ��*/
	void searchBookByNameOption(pBookInfo head) {
		char name[128] = { 0 };
		pBookInfo target = NULL;
		clearScreen();
		cout << "        ��------------------------��\n";
		cout << "               #��������ѯ#\n";
		cout << "             ������";
		cin >> name;
		cout << "        ��------------------------��\n";
		target = findBookInfoNodeByName(head, name);
		if (target) {
			do {
				showBook(target);
				target = findBookInfoNodeByName(target->next, name);
			} while (target);
		}
		else {
			cout << "\nδ�ҵ���ͼ�飡\n";
		}
		waitingPressAnyKey();
	}

	/*�����浥λ��ѯͼ��ѡ��*/
	void searchBookByPressOption(pBookInfo head) {
		char press[128] = { 0 };
		pBookInfo target = NULL;
		clearScreen();
		cout << "        ��------------------------��\n";
		cout << "               #�����浥λ��ѯ#\n";
		cout << "             ������";
		cin >> press;
		cout << "        ��------------------------��\n";
		target = findBookInfoNodeByPress(head, press);
		if (target) {
			do {
				showBook(target);
				target = findBookInfoNodeByPress(target->next, press);
			} while (target);
		}
		else {
			cout << "\nδ�ҵ���ͼ�飡\n";
		}
		waitingPressAnyKey();
	}

	/*������ѯͼ��ѡ��*/
	void searchBookByStockOption(pBookInfo head) {
		int min, max;
		pBookInfo target = NULL;
		clearScreen();
		cout << "        ��------------------------��\n";
		cout << "               #������ѯ#\n";
		cout << "             ��������ڵ��ڣ�";
		cin >> min;
		cout << "             �����С�ڵ��ڣ�";
		cin >> max;
		cout << "        ��------------------------��\n";
		target = findBookInfoNodeByStock(head, min, max);
		if (target) {
			do {
				showBook(target);
				target = findBookInfoNodeByStock(target->next, min, max);
			} while (target);
		}
		else {
			cout << "\nδ�ҵ���ͼ�飡\n";
		}
		waitingPressAnyKey();
	}

	/*ͼ������˵�*/
	void browseBooksOption(pBookInfo head) {
		int option;
		while (1) {
			clearScreen();
			cout << "        ��-------------------------------��\n";
			cout << "                 #ͼ�����#\n";
			cout << "\n";
			cout << "              ��1�� ͼ���嵥\n";
			cout << "              ��2�� ��ISBN��ѯ\n";
			cout << "              ��3�� ��������ѯ\n";
			cout << "              ��4�� �����浥λ��ѯ\n";
			cout << "              ��5�� ���������ѯ\n";
			cout << "              ��0�� ����\n";
			cout << "\n";
			cout << "        ��-------------------------------��\n";
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

	/*ͼ�����˵�*/
	void manageBooksOption(pBookInfo* head) {
		int option;
		while (1) {
			clearScreen();
			cout << "        ��-------------------------------��\n";
			cout << "                 #ͼ�����#\n";
			cout << "\n";
			cout << "              ��1�� ���ͼ��\n";
			cout << "              ��2�� �޸�ͼ��\n";
			cout << "              ��3�� ɾ��ͼ��\n";
			cout << "              ��0�� ����\n";
			cout << "\n";
			cout << "        ��-------------------------------��\n";
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

	/*�ɹ�*/
	void inputStock(pBookInfo head) {
		char isbn[128] = { 0 };
		pBookInfo target = NULL;
		clearScreen();
		cout << "        ��------------------------��\n";
		cout << "               #�ɹ�#\n";
		cout << "             ISBN��";
		cin >> isbn;
		cout << "        ��------------------------��\n";
		target = findBookInfoNodeByISBN(head, isbn);
		if (target) {
			int number;
			showBook(target);
			cout << "        ��------------------------��\n";
			cout << "             �ɹ�������";
			scanf("%d", &number);
			cout << "       ��------------------------��\n";
			if (number > 0) {
				target->stock += number;
				/*ͬ���ļ���Ϣ*/
				saveBookInfoFile(head);
				cout << "\n�����ɹ���\n";
			}
			else {
				cout << "\n������ʧ�ܣ��ɹ�����Ӧ�ô���0��\n";
			}
		}
		else {
			cout << "\nδ�ҵ���ͼ�飡\n";
		}
		waitingPressAnyKey();
	}

	/*����*/
	void outputStock(pBookInfo head) {
		char isbn[128] = { 0 };
		pBookInfo target = NULL;
		clearScreen();
		cout << "        ��------------------------��\n";
		cout << "               #����#\n";
		cout << "             ISBN��";
		cin >> isbn;
		cout << "        ��------------------------��\n";
		target = findBookInfoNodeByISBN(head, isbn);
		if (target) {
			int number;
			showBook(target);
			cout << "        ��------------------------��\n";
			cout << "             ����������";
			cin >>number;
			cout << "        ��------------------------��\n";
			if (target->stock - number >= 0) {
				target->stock -= number;
				/*ͬ���ļ���Ϣ*/
				saveBookInfoFile(head);
				cout << "\n�����ɹ���\n";
			}
			else {
				cout << "\n������ʧ�ܣ�û���㹻�Ŀ�棡\n";
			}
		}
		else {
			cout << "\nδ�ҵ���ͼ�飡\n";
		}
		waitingPressAnyKey();
	}

	/*���˵�*/
	void menu(pBookInfo* head) {
		while (1) {
			int option;
			clearScreen();
			cout << "        ��-------------------------------��\n";
			cout << "               #ͼ�����ϵͳ#\n";
			cout << "\n";
			cout << "              ��1�� ���ͼ��\n";
			cout << "              ��2�� ͼ�����\n";
			cout << "              ��3�� �ɹ�\n";
			cout << "              ��4�� ����\n";
			cout << "              ��0�� �˳�ϵͳ\n";
			cout << "\n";
			cout << "        ��-------------------------------��\n";
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