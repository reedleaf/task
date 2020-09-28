
#include <iostream>
#include <string>
#include <vector>
using std::cout;
using std::endl;
using std::string;
using std::vector;

/*      查找时间复杂度O(n)
 *      插入和删除时间复杂度O(n) + O(1)
 */

/*
#define DataType string

typedef struct ListNode{
    DataType data;
    struct ListNode* next;
    ListNode(){}
    ListNode(DataType data):data(data){}
}Node;

class List{
private:
    Node* list;
    Node* tail;

public:
    List()
    {
        list = new Node;
        list->next = nullptr;
    }
    ~List()
    {
        Node* p = list->next;
        while(p)
        {
            delete list;
            list = p;
            p = p->next;
        }
        delete list;
        cout << "list clear end!" << endl;
    }

public:
    //insert node to list
    //头插
    string insert_head(const DataType& data)
    {
        Node* node = new Node(data);
        node->next = list->next;
        list->next = node;
        return "OK head!";
    }
    //尾插
    string insert_tail(const DataType& data)
    {
        Node* node = new Node(data);
        if(!list->next)
        {
            node->next = list->next;
            list->next = node;
            tail = node;
        }
        else
        {
            tail->next = node;
            tail = node;
        }
        return "OK tail!";
    }
    //print list
    void print()
    {
        Node* p = list->next;
        while(p)
        {
            cout << p->data << "->";
            p = p->next;
        }
    }
    //statistics list length
    int length()
    {
        int count = 0;
        Node* p = list->next;
        while(p)
        {
            count++;
            p = p->next;
        }
        list->data = count;
        return count;
    }
    //插入节点到第i个位置
    string insertPos(const DataType &data, int pos)
    {
        int i = 0;
        Node* p = list->next;
        Node* q = list;
        while(p)
        {
            if(pos == i)
            {
                Node* node = new Node(data);
                node->next = p;
                q->next = node;
                return "success!";
            }
            i++;
            p = p->next;
            q = q->next;
        }
        return "failure!";
    }
    //指定位置删除节点
    string delNode(int pos)
    {
        int i = 0;
        Node* p = list->next;
        Node* q = list;
        while(p)
        {
            if(pos == i)
            {
                p = p->next;
                Node* del_node = q->next;
                delete del_node;
                q->next = p;
                return "delete success!";
            }
            i++;
            p = p->next;
            q = q->next;
        }
        return "delete failure！";
    }
};

int main()
{
    List list;
    vector<DataType> v{"CLion","File","Edit","View","Code","Run","Tools","VCS","Window","Help"};

    //插入节点
    for(const DataType &data : v)
    {
        //cout << list.insert_head(data) << endl;
        cout << list.insert_tail(data) << endl;
    }
    //长度
    cout << "list length：" << list.length() << endl;
    //打印
    list.print();
    cout << endl;

    //指定地方插入节点
    string str = "appointData";
    cout << list.insertPos(str,2) << endl;
    cout << "list length：" << list.length() << endl;
    list.print();
    cout << endl;

    //指定位置删除节点
    cout << list.delNode(10) << endl;
    cout << "list length：" << list.length() << endl;
    list.print();
    return 0;
}
*/
