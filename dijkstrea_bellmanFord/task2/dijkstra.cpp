#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <queue>
#include <assert.h>
using namespace std;

#define FILENAME "input.txt"
#define INF 0x3f3f3f3f

struct qNode{
	int v;
	double distance;
	friend bool operator < (const qNode& a, const qNode& b)
	{
		return a.distance > b.distance;
	}
};

class Dijkstra {
public:
	Dijkstra();
	~Dijkstra();

public:
	void dijkstra();

private:
	void save();
	void savePath(int u,int v);

private:
	vector<double> dis;
	vector<int> path;
	vector<int> shortestPath;
	double **G;
	int start;
	int n;
};

Dijkstra::Dijkstra()
{
	fstream in(FILENAME);
	if (!in.is_open())
	{
		assert("file open failure!");
		exit(1);
	}
	in >> n;
	in >> start;
	start -= start;

	G = new double*[n];
	for (int i = 0; i < n; ++i)
	{
		G[i] = new double[n];
		fill(G[i], G[i] + n, INF);
	}

	int u, v;
	double cost;
	while (in >> u >> v >> cost)
		G[u][v] = cost;


}

Dijkstra::~Dijkstra()
{
	save();
	cout << "输出文件保存成功！" << endl;
	for (int i = 0; i < n; ++i)
	{
		delete G[i];
		G[i] = nullptr;
	}
	delete [] G;
	G = nullptr;
}

void Dijkstra::dijkstra()
{
	vector<int> visited;
	for (int i = 0; i < n; ++i)
	{
		visited.push_back(0);
		dis.push_back(INF);
		if (dis[i] < INF)
			path.push_back(start);
		else
			path.push_back(-1);
	}
	priority_queue<qNode> q;
	dis[start] = 0;
	qNode node{start,dis[start]};
	q.push(node);
	while (!q.empty())
	{
		int v = q.top().v;
		q.pop();
		if (visited[v])
			continue;
		else
			visited[v] = 1; 
		for (int i = 0; i < n; ++i)
		{
			if (!visited[i] && dis[v] + G[v][i] < dis[i])
			{
				dis[i] = dis[v] + G[v][i];
				path[i] = v;
				qNode node{ i,dis[i] };
				q.push(node);
			}
		}
	}
}

void Dijkstra::save()
{
	fstream out;
	out.open("output.txt", ios::out);
	char buffer[100];
	vector<char> title(n,'Z');
	for (int i = 0; i < n; ++i)
		title[i] = title[i] - n + i;
	title[start] = 'S';


	for (int i = 0; i < n; ++i)
	{
		if (i == start)
			sprintf(buffer, "%c=%.2lf;path=<%s>", title[start], 0.0, "");
		else
		{
			string pathBuf;
			savePath(start, i);
			for (int i = 0; i < shortestPath.size(); ++i)
			{
				pathBuf += title[shortestPath[i]];
				if (i != shortestPath.size() - 1)
					pathBuf += ',';
			}
			sprintf(buffer, "%c=%.2lf;path=<%s>",title[i] , dis[i], pathBuf.c_str());
		}
		out << buffer << "\n";
		shortestPath.clear();
	}
	out.close();
}

void Dijkstra::savePath(int u,int v)
{
	if (u == v)
	{
		shortestPath.push_back(u);
		return;
	}
	savePath(u, path[v]);
	shortestPath.push_back(v);
}

int main()
{
	Dijkstra d;
	d.dijkstra();
	return 0;
}