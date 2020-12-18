#include "graphAlgorithm.h"

void menu(GraphAlgorithm& G,string output)
{
    int choice;
    while(true)
    {
        system("cls");
        cout << "***************���·��***************" << endl;
        cout << "��0���˳��ұ����ļ�"<<endl;
        cout << "��1��Dijkstra�㷨"<<endl;
        cout << "��2��BellmanFord�㷨" <<endl;
        cout << "����ѡ��:" << endl;
        cin >> choice;
        switch (choice)
        {
            case 0:G.write(output);
                    return;
            case 1:G.dijkstra();
                    break;
            case 2:G.bellmanFord();
                    break;
            default:cout << "ѡ�����" << endl;
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

