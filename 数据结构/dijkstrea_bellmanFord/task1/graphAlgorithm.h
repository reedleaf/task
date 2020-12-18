//
// Created by reedleaf on 2020/12/17.
//

#ifndef GRAPHALGORITHM_H
#define GRAPHALGORITHM_H

#include <queue>
#include <vector>
#include <string>
#include <iostream>
#include <set>
using namespace std;
#define INF 0x3f3f3f3f

//�������ȶ��еĽṹ��
typedef struct Node{
    int index;      //����������±�
    int dis;        //��ʼ���㵽�˶������̾���

    Node(){}
    Node(int _index,int _dis):index(_index),dis(_dis){}
    friend bool operator < (const Node &a, const Node &b)
    {
        return a.dis > b.dis;       //����<���������dС�����ȶȸ�
    }
}node;

typedef struct Edge{
    int begin;
    int end;
    double distance;
}edge;

class GraphAlgorithm {
private:
    vector<vector<double>> map;    //ͼ
    vector<edge> edges;
    set<int> vertex;            //����ϼ�
    vector<int> path;
    vector<double> dis_d;            //��ʼ�㵽ÿ�������С����
    vector<double> dis_b;   
    vector<vector<int>> dijkstraPath;
    vector<vector<int>> bellmanFordPath;
    int beginVertex;
    int tag;

public:
    GraphAlgorithm(string filename);

private:
    void init();
    void read(string filename);
    void getDijkstraPath(int index,int v,int w);
    void getBellmanFordPath(const vector<int>& path,int root,int cur);

public:
    void dijkstra();
    void bellmanFord();
    void write(string filename);


};



#endif //GRAPHALGORITHM_H

















