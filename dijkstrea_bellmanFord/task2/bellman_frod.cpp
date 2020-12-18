#include <iostream>
#include <vector>
#include <string>
#include <assert.h>
#include <algorithm>
#include <fstream>
using namespace std;
#define INF 0x3f3f3f3f
#define INPUTFILE "input.txt"
#define OUTPUTFILE "output.txt"

struct Edge
{
	int u;
	int v;
	double cost;
};

class BellmanFord {
public:
	BellmanFord();
	~BellmanFord();

public:
	void bellmanFord();

private:
	void save();
	void saveShortestPath(vector<int>& shortestPath, int v);

private:
	vector<Edge> edge;
	vector<int> path;
	vector<double> dis;
	int start;
	int n;
};

BellmanFord::BellmanFord()
{
	fstream fp(INPUTFILE);
	if (!fp.is_open())
	{
		assert("file open failure!");
		exit(1);
	}
	fp >> n;
	fp >> start;
	start -= 1;

	Edge e;
	while (fp >> e.u >>e.v >> e.cost)
		edge.push_back(e);

	dis.resize(n);
	path.resize(n);
	fill(dis.begin(), dis.end(), INF);
	fill(path.begin(), path.end(), start);
	fp.close();

}

BellmanFord::~BellmanFord()
{
	save();
	cout << "输出文件已保存!" << endl;
}

void BellmanFord::bellmanFord()
{
	dis[start] = 0;
	for (int i = 0; i < n - 1; ++i)
	{
		int ck = 0;
		for (int j= 0; j < edge.size(); ++j)
		{
			if (dis[edge[j].v] > dis[edge[j].u] + edge[j].cost)
			{
				dis[edge[j].v] = dis[edge[j].u] + edge[j].cost;
				path[edge[j].v] = edge[j].u;
				ck = 1;
			}
		}
		if (0 == ck)
			break;
	}
	int flag = 0;
	for (int i = 0; i < edge.size(); ++i)
	{
		if (dis[edge[i].v] > dis[edge[i].u] + edge[i].cost)
		{
			flag = 1;
			break;
		}
	}
	if (flag)
	{
		cout << "负权回路！" << endl;
		system("pause");
		exit(1);
	}
}

void BellmanFord::save()
{
	FILE* fp = fopen(OUTPUTFILE, "w");
	char buffer[100];
	vector<char> title(n, 'Z');
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
			vector<int> shortestPath;
			saveShortestPath(shortestPath, i);
			reverse(shortestPath.begin(), shortestPath.end());
			for (int i = 0; i < shortestPath.size(); ++i)
			{
				pathBuf += title[shortestPath[i]];
				if (i != shortestPath.size() - 1)
					pathBuf += ',';
			}
			sprintf(buffer, "%c=%.2lf;path=<%s>", title[i], dis[i], pathBuf.c_str());
		}
		fprintf(fp, "%s\n", buffer);
	}
	fclose(fp);
}

void BellmanFord::saveShortestPath(vector<int>& shortestPath,int v)
{
	while (v != path[v])
	{
		shortestPath.push_back(v);
		v = path[v];
	}
	if (v == path[v])
		shortestPath.push_back(v);
}

int main()
{
	BellmanFord b;
	b.bellmanFord();
	return 0;
}
