//
// Created by reedleaf on 2020/9/28.
//

#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;
//KMP重点是next数组

//next数组
void nextArray(string& next,const string& T)
{
    next[0] = 0;//第一个永远为0
    int j = 0;//j是后面一个字符指针
    int k = -1;//k是前面字符指针

    while(j < T.size() - 1)//j表示字符长度
    {
        if(k == -1 || T[k] == T[j])//无论第一个是不是等于第二个字符，都是0，例如s=aaca s[0]=s[1]在next中，next[1]也是0
        {
            //指针往后移动
            ++k;
            ++j;
            //next[j]中就表示着前缀位置
            next[j] = k;
        }
        else
        {
            //如果有字符不相等了,回溯到前面一个前缀
            k = next[k];
        }
    }
}

int KMP(const string& S,const string& T)
{
    string next;
    nextArray(next,T);
    int j = 0;
    int i = 0;
    while(j < S.size() - 1 && i < T.size())
    {
        if(j == -1 || S[i] == T[i])
        {
            i++;
            j++;
        }
        else
        {
            j = next[j];
        }
    }
    if(j == S.size())
        return i - j;
    else
        return -1;
}


int main(int argc,const char* argv[])
{
    string S = "abxabcabcaby";
    string T = "abcaby";
    cout << KMP(S,T) << endl;
    return 0;
}