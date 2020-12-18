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

//放入优先队列的结构体
typedef struct Node{
    int index;      //顶点数组的下标
    int dis;        //开始顶点到此顶点的最短距离

    Node(){}
    Node(int _index,int _dis):index(_index),dis(_dis){}
    friend bool operator < (const Node &a, const Node &b)
    {
        return a.dis > b.dis;       //重载<运算符，令d小的优先度高
    }
}node;

typedef struct Edge{
    int begin;
    int end;
    double distance;
}edge;

class GraphAlgorithm {
private:
    vector<vector<double>> map;    //图
    vector<edge> edges;
    set<int> vertex;            //顶点合集
    vector<int> path;
    vector<double> dis_d;            //开始点到每个点的最小距离
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

















