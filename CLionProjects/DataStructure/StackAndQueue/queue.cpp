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
//循环队列不写了
//front = (front + 1) % MAXSIZE
//rear = (rear + 1) % MAXSIZE
typedef struct QueueNode{
    DataType data;
    struct QueueNode* next;

    QueueNode(){}
    QueueNode(DataType _data):data(_data),next(nullptr){}
}Node;

typedef struct{
    struct QueueNode *front,*rear;
}LinkNode;

class Queue{
private:
    LinkNode linkNode;
    LinkNode *test;

public:
    Queue()
    {
        linkNode.front = nullptr;
        linkNode.rear = nullptr;
    }

public:
    //进队列
    void enQueue(const DataType& data)
    {
        Node *node = new Node(data);
        if(linkNode.front == nullptr)
        {
            linkNode.front = node;
            linkNode.rear = node;
        }
        else
        {
            linkNode.rear->next = node;
            linkNode.rear = node;
        }
    }
    //打印队列
    void printQueue()
    {
        LinkNode q = linkNode;
        while(q.front)
        {
            cout << q.front->data << "->";
            q.front = q.front->next;
        }
    }
};
int main(int argc,const char* argv[])
{
    Queue queue;

    queue.enQueue(1);
    queue.enQueue(2);
    queue.enQueue(3);
    queue.enQueue(4);

    queue.printQueue();
    return 0;
}*/