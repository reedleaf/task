#include <iostream>
#include <unistd.h>
#include <string>
#include <fcntl.h>
#include <cstring>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

char* argv[4][10] = {{"cat","country.txt","city.txt",NULL},
                     {"egrep","g",NULL},
                     {"sort",NULL},
                     {"more",NULL}
                    };

void splitCommand(string command,vector<string>& v,string& filename)
{
    string temp;
    for(size_t i = 0;i < command.size();++i)
    {
        if(command[i] == '>')
        {
            filename = command.substr(i + 1, command.size() - i);
            v.push_back(temp);
        }
        if(command[i] == '|')
        {
            v.push_back(temp);
            temp.clear();
        }
        else
            temp += command[i];
    }
}
void fork_child(int *fd,string s,int i)
{
//    char* argv[10];
    close(1);
    close(fd[0]);
    dup2(fd[1],1);
    string temp;
    int j = 0;
//    stringstream buf(s);
//    while(buf >> temp)
//    {
//        argv[j] = new char[10];
//        strcpy(argv[j++],temp.c_str());
//    }
//    argv[j] = new char;
//    argv[j] = (char*)0;
   // cout << argv[0] << endl;
    if(execvp(argv[i][0],argv[i]) < 0)
    {
        perror(argv[i][0]);
        exit(-1);
    }

}
void fork_parent(int* fd_read,int *fd_write,string s,int i)
{


    string temp;
    int j = 0;
    stringstream buf(s);
//    while(buf >> temp)
//    {
//        argv[j] = new char[10];
//        strcpy(argv[j++],temp.c_str());
//    }
//    argv[j] = new char;
//    argv[j] = (char*)0;
    close(0);
    close(fd_read[1]);
    dup2(fd_read[0],0);

//    close(1);
//    close(fd_write[0]);
//    dup2(fd_write[1],1);
    if(execvp(argv[i][0],argv[i]) < 0)
    {
        perror(argv[i][0]);
        exit(-1);
    }
}

//cat country.txt city.txt | egrep 'g' | sort | more > countryCitySorted.txt
int main()
{


    string filename;
    string command;
    getline(cin,command);
    vector<string> v;
    splitCommand(command,v,filename);


    int fd[2],fd_1[2],fd_2[2],fd_3[2];

    if(pipe(fd) < 0 || pipe(fd_1) < 0|| pipe(fd_2) < 0|| pipe(fd_3)< 0)
    {
        perror("pipe error!");
        return 0;
    }
    pid_t pid,pid1,pid2,pid3;
    //fork()*****************************
    if((pid = fork()) == 0)
    {
        fork_child(fd,v[0],0);
        cout << "第一个子"<<endl;
    }
    else
    {
        wait(&pid);
        //0in 1out 2 error

        if((pid1 = fork()) == 0)
        {
            //处理第二个管道
            fork_parent(fd,fd_1,v[1],1);
            cout << "第二个子"<<endl;
        }
        else
        {
            wait(&pid1);
            if((pid2 = fork()) == 0)
            {
                //处理第三个管道
                fork_child(fd,v[1],2);
                //fork_parent(fd_1,fd_2,v[2],2);
                cout << "第三个子"<<endl;
            }
            else
            {
                wait(&pid2);
                if((pid3 = fork()) == 0)
                {
                    //处理第四个管道
                    fork_parent(fd,fd_3,v[3],3);
                    cout << "第四个子"<<endl;
                }
                else
                {
                    wait(&pid3);
//                    char buf[256];
//                    close(fd_3[1]);
//                    cout << read(fd_3[0],buf,sizeof(buf));
                    cout << "父" << endl;
                }
            }
        }
    }
    //fd end
    return 0;
}