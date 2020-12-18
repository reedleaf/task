#define _CRT_SECURE_NO_WARNINGS
#include "graphAlgorithm.h"
#include <fstream>
#include <sstream>
#include <algorithm>

GraphAlgorithm::GraphAlgorithm(string filename)
{
    tag = -1;
    read(filename);
    init();
}

void GraphAlgorithm::init()
{
    size_t n = vertex.size();
    map.resize(n);
    dijkstraPath.resize(n);
    bellmanFordPath.resize(n);

    //初始化图
    for(size_t i = 0;i < n;++i)
        for(size_t j = 0;j < n;++j)
            map[i].push_back(INF);

    for(const auto& it : edges) {
        map[it.begin][it.end] = it.distance;
    }
}

void GraphAlgorithm::read(string filename)
{
    fstream infile(filename.c_str());
    if(!infile.is_open())
    {
        cout << "文件" << filename << "打开失败！" << endl;
        system("pause");
        exit(1);
    }
    string str;
    bool flag = true;
    //第一行几个顶点没用
    getline(infile,str);
    while(getline(infile,str))
    {
        stringstream buffer(str);
        if(flag)
        {
            buffer >> beginVertex;
            flag = false;
        }
        else {
            edge e;
            buffer >> e.begin >> e.end >> e.distance;
            edges.push_back(e);
            //所有顶点关系的顶点都放进去，剩下的就是不重复的所有顶点
            vertex.insert(e.begin);
            vertex.insert(e.end);
        }
    }
    infile.close();
}

void GraphAlgorithm::dijkstra()
{
    tag = 0;
    init();
    int v = beginVertex - 1;
    vector<int> visited;        //记录访问过的最小点

    size_t n = vertex.size();
    //初始化path,dis,visited;
    for(size_t i = 0;i < n;++i)
    {
        //开始全都未访问
        visited.push_back(0);
        //dis和普通的不一样，当队列第一次出队，相当于把开始结点v到每个点的距离初始化在dis中
        dis_d.push_back(INF);
        //如果v到其他点有路径，当然最短路径的前驱就是v了
        if(dis_d[i] < INF)
            path.push_back(v);
        else
            path.push_back(-1);
    }

    priority_queue<node> q;     //优先队列
    //////////////////优先队列实现////////////////////
    //省了一次找最小距离结点的循环
    dis_d[v] = 0;
    q.push(node(v,dis_d[v]));
    while(!q.empty())
    {
        //取距离最小的，第一次是自己
        v = q.top().index;
        q.pop();
        if(visited[v])
            continue;
        else
            visited[v] = 1;
        for(size_t w = 0; w < n ; ++w)
        {
            //找到最小路径的不会访问，所以不会放在队列中
            if(!visited[w] && dis_d[v] + map[v][w] < dis_d[w])
            {
                dis_d[w] = dis_d[v] + map[v][w];
                path[w] = v;
                //把当前较小的结点记录，下次取最小的结点更新
                q.push(node(w,dis_d[w]));
            }
        }
    }

    for(size_t i = 0; i < n;++i)
    {
        getDijkstraPath(i,beginVertex - 1,i);
    }

}

void GraphAlgorithm::bellmanFord()
{
    tag = 1;
    size_t n = vertex.size();
 
    vector<int> path(n,beginVertex - 1);
	dis_b.resize(n);
    
    
    fill(dis_b.begin(),dis_b.end(),INF);
    dis_b[beginVertex - 1] = 0;
    
    
    for(size_t k = 0;k < n -1;++k)
    {
    	//检查松弛有没有更新最小值，没有更新则表示是最小值了，退出 
    	bool check = false;
    	for(size_t i = 0;i < edges.size();++i)
		{
			if(dis_b[edges[i].end] > dis_b[edges[i].begin] + edges[i].distance)
			{
				dis_b[edges[i].end] = dis_b[edges[i].begin] + edges[i].distance;
				path[edges[i].end] = edges[i].begin;
				check = true;
			}
		} 
		if(!check)
			break;
	}
	bool flag = false;
	for(size_t i = 0;i < edges.size();++i)
	{
		if(dis_b[edges[i].end] > dis_b[edges[i].begin] + edges[i].distance)
		{
			flag = true;
			break;
		}
	}
	if(flag)
	{
		cout << "此图包含有负权回路！" << endl;
		system("pause");
		exit(1);
	}
	else
	{
		for(size_t i = 0;i < n;++i)
    	{
        	getBellmanFordPath(path,i,i);
    	}
	}
    
}


void GraphAlgorithm::write(string filename)
{
    if(tag == -1)
        return;
    FILE *fp;
    fp = fopen(filename.c_str(),"w");
    if(!fp)
    {
        cout << "文件" << filename << "打开失败！" << endl;
        system("pause");
        exit(1);
    }
    vector<vector<int>> path;
    if(tag == 0)
        path = dijkstraPath;
    else if(tag == 1)
        path = bellmanFordPath;

    char ch = 'Z' - vertex.size() + 1;
    vector<char> v;
    for(size_t i = 0;i < vertex.size();++i)
        v.push_back(ch++);
    for(size_t i = 0;i < path.size();++i)
    {
        string str;
        for (size_t j = 0; j < path[i].size(); ++j)
        {
            str += v[path[i][j]];
            if(j != path[i].size() - 1)
                str += ',';
        }
        //最短路径保存在map中
        if(tag == 0)
            fprintf(fp,"%c=%.2lf;path=<%s>\n",v[i],dis_d[i],str.c_str());
		if (tag == 1)
		{
			reverse(str.begin(), str.end());
			fprintf(fp, "%c=%.2lf;path=<%s>\n", v[i], dis_b[i], str.c_str());
		}
    }
    fclose(fp);
}

void GraphAlgorithm::getDijkstraPath(int index,int v,int w)
{
    if(v == w)
    {
        dijkstraPath[index].push_back(v);
        return;
    }
    getDijkstraPath(index,v,path[w]);
    dijkstraPath[index].push_back(w);
}

void GraphAlgorithm::getBellmanFordPath(const vector<int>& path,int root,int cur)
{
    while(root != path[root])
    {
        bellmanFordPath[cur].push_back(root);
        root = path[root];
    }
    if(root == path[root])
    	bellmanFordPath[cur].push_back(root);
}


