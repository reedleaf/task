//
// Created by reedleaf on 2020/9/27.
//
/*
#include <iostream>
#include <string>
#include <vector>
using std::cout;
using std::endl;
using std::string;
using std::vector;

#define DataType int

typedef struct ListNode{
    DataType data;
    struct ListNode* next;
    ListNode(){}
    ListNode(DataType data):data(data){}
}Node;

class List {
private:
    Node *list;
    Node *tail;

public:
    friend void combined(const List &list_1,const List &list_2);

public:
    List() {
        list = new Node;
        list->next = nullptr;
    }

    ~List() {
        Node *p = list->next;
        while (p) {
            delete list;
            list = p;
            p = p->next;
        }
        delete list;
        cout << "list clear end!" << endl;
    }

public:
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
    void print()
    {
        Node* p = list->next;
        while(p)
        {
            cout << p->data << "->";
            p = p->next;
        }
    }
};

void link(Node*& listEnd,Node*& newNode,Node*& tail)
{
    if(!listEnd->next)
    {
        newNode->next = listEnd->next;
        listEnd->next = newNode;
        tail = newNode;
    }
    else
    {
        tail->next = newNode;
        tail = newNode;
    }
}

void combined(const List &list_1,const List &list_2)
{
    Node* listEnd = new Node;
    Node* tail;
    Node* p = list_1.list->next;
    Node* q = list_2.list->next;

    while(p && q)
    {
        Node* newNode;
        if(p->data < q->data) {
            newNode = new Node(p->data);
            p = p->next;
        }else {
            newNode = new Node(q->data);
            q = q->next;
        }

        link(listEnd,newNode,tail);

    }
    if(q)
        tail->next = q;
    if(p)
        tail->next = p;

    p = listEnd->next;
    while(p)
    {
        cout << p->data << "->";
        p = p->next;
    }
}


int main(int argc,const char* argv[])
{
    vector<DataType> v1{1,3,5,7,9};
    vector<DataType> v2{2,4,6,8,10};

    //建立两个有序链表
    List list_1;
    List list_2;

    for(auto const &value : v1)
        list_1.insert_tail(value);
    for(auto const &value : v2)
        list_2.insert_tail(value);

    cout << "list_1：";
    list_1.print();
    cout << endl;
    cout << "list_2：";
    list_2.print();
    cout << endl;

    combined(list_1,list_2);
    cout << endl;

    return 0;
}
 */