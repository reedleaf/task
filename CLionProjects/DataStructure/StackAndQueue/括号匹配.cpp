//
// Created by reedleaf on 2020/9/28.
//
/*
#include <iostream>
#include <string>
#include <vector>
using std::cout;
using std::endl;
using std::string;
using std::vector;

#define DataType char
#define MAXSIZE 100

class Stack {
private:
    int m_top;
    int m_curSize;
    DataType m_stack[MAXSIZE];

public:
    Stack() : m_top(-1), m_curSize(0) {}

public:
    //push
    int checkBracket(const DataType &data) {
        if (m_curSize >= MAXSIZE) {
            cout << "current memory is full!" << endl;
        }
        if(data == '(' || data == '[' || data == '{'){
            m_stack[++m_top] = data;
            m_curSize++;
        }else if(data == ')' || data == ']' || data == '}'){
            if(m_top == -1)
            {
                cout << "栈已空！" << data << "不匹配" << endl;
                return 2;
            }
            int temp = m_top;
            switch (data)
            {
                case ')':
                    if(m_stack[m_top] == '(')
                        m_top--;
                    break;
                case ']':
                    if(m_stack[m_top] == '[')
                        m_top--;
                    break;
                case '}':
                    if(m_stack[m_top] == '{')
                        m_top--;
                    break;
            }
            if(temp == m_top)
            {
                cout << "括号交叉问题！" << endl;
                return 1;
            }
        }
        return 0;
    }
    const int& getTopIndex(){return m_top;}
};

int main(int argc,const char* argv[])
{
    vector<DataType> v{'(','a','*','b','+','c',')','-','d',')'};
    Stack stack;

    for(const DataType& value : v)
    {
        if(stack.checkBracket(value))
            break;
    }

    if(stack.getTopIndex() == -1)
        cout << "括号匹配成功！" << endl;
    else
        cout << "左括号多于右括号！ " << endl;
    return 0;
}
*/