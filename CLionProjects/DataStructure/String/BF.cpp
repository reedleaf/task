/*
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

//只写字符串的子串匹配  BF和KMP
//BF暴力求解，子串从主串的第一个字符开始匹配，失败再往下一个匹配，直到主串匹配完，就是无匹配，否则返回起始位置

int BF(const string& S,const string& T)
{
    bool flag;
    //主串S  子串T
    for (int i = 0; i < S.size(); ++i)
    {
        int k = i;
        flag = false;
        for (int j = 0; j < T.size(); ++j)
        {
            if(S[k] != T[j]) {
                flag = true;
                break;
            }
            k++;
        }
        if(!flag)
            return i + 1;
    }
    return -1;
}

int main(int argc,const char* argv[])
{
    string S = "aaaaabcckd";
    string T = "bcckd";
    cout << "子串起始位置：" << BF(S,T) << endl;
    return 0;
}
 */