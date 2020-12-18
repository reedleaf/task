#include "graphAlgorithm.h"

void menu(GraphAlgorithm& G,string output)
{
    int choice;
    while(true)
    {
        system("cls");
        cout << "***************最短路径***************" << endl;
        cout << "【0】退出且保存文件"<<endl;
        cout << "【1】Dijkstra算法"<<endl;
        cout << "【2】BellmanFord算法" <<endl;
        cout << "输入选择:" << endl;
        cin >> choice;
        switch (choice)
        {
            case 0:G.write(output);
                    return;
            case 1:G.dijkstra();
                    break;
            case 2:G.bellmanFord();
                    break;
            default:cout << "选择错误！" << endl;
        }
        system("pause");
    }
}

int main()
{
    string filename("data.txt");
    string output("output.txt");
    GraphAlgorithm G(filename);
    menu(G,output);
    return 0;
}

