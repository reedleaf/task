//
// Created by reedleaf on 2020/9/25.
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
    struct ListNode *next,*front;
    ListNode(){}
    ListNode(DataType data):data(data),next(nullptr),front(nullptr){}
}Node;

class BothWayList{
private:
    Node* list;

public:
    BothWayList()
    {
        list = new Node(-1);
    }
    ~BothWayList()
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
    //插入节点
    void insert(const DataType& data)
    {
        Node* node = new Node(data);

        if(!list->next)
        {
            node->next = list->next;
            node->front = list;
            list->next = node;
        }
        else
        {
            Node* p = list->next;
            node->next = p;
            node->front = list;
            p->front = node;
            list->next = node;
        }
    }
    //返回指定位置节点的前一个元素
    DataType getAppointData(DataType data)
    {
        Node* p = list->next;

        while(p)
        {
            if(p->data == data)
                return p->front->data;

            p = p->next;
        }
        return -2;
    }
    //删除一个节点
    void deleteElement(DataType data)
    {
        Node* p = list->next;
        Node* q = list;

        while(p)
        {
            if(p->data == data)
            {
                p = p->next;
                Node* temp = q->next;
                delete temp;

                q->next = p;
                p->front = q;
            }
            p = p->next;
            q = q->next;
        }
    }
    //打印next和front
    void print()
    {
        Node* p = list;
        Node* q;
        while(p)
        {
            if(p->next == nullptr)
                q = p;
            cout << p->data << "->";
            p = p->next;

        }
        cout << endl;
        while(q)
        {
            cout << q->data << "->";
            q = q->front;
        }
    }
};

int main()
{
    BothWayList list;
    vector<int> v{1,2,3,4,5,6,7,8,9};

    for(const DataType& data : v)
    {
        list.insert(data);
    }

    list.deleteElement(2);

    DataType data = list.getAppointData(1);
    if(data == -2)
        cout << "No This Element！";
    else
        cout << "Find This Element：" << data << endl;

    list.print();
    return 0;
}
*/