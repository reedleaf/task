/*
#include <iostream>
#include <string>
#include <vector>
using std::cout;
using std::endl;
using std::string;
using std::vector;

#define DataType int
#define MAXSIZE 100

class Stack{
private:
    int m_top;
    int m_curSize;
    DataType m_stack[MAXSIZE];

public:
    Stack():m_top(-1),m_curSize(0){}

public:
    //push
    void push(const DataType& data)
    {
        if(m_curSize >= MAXSIZE)
        {
            cout << "current memory is full!" << endl;
        }
        m_stack[++m_top] = data;
        m_curSize++;
    }
    //pop
    void pop()
    {
        if(m_top == -1)
        {
            cout << "stack is empty!" << endl;
        }
        else
        {
            m_top--;
            m_curSize--;
        }
    }
    //return size
    const int& size()
    {
        return m_curSize;
    }
    //return current top
    const DataType& top()
    {
        return m_stack[m_top];
    }

};

int main(int argc,const char* argv[])
{
    Stack stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(4);
    stack.push(5);
    stack.push(8);

    cout << "current size：" << stack.size() << endl;
    cout << "current top：" << stack.top() << endl;
    return 0;
}
 */