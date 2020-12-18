#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <queue>
#include <algorithm> 
using namespace std;

#define MAX 10000

class DijkstraAndBellmanFord {
public:
	DijkstraAndBellmanFord()
	{
		fstream in("file.txt");
		if (!in.is_open())
		{
			cout << "failure!" << endl;
			exit(1);
		}
		in >> size;
		in >> origin;
		origin -= origin;

		graph = new double*[size];
		for (int i = 0; i < size; ++i)
		{
			graph[i] = new double[size];
			fill(graph[i], graph[i] + size, MAX);
		}

		Edge e;
		while (in >> e.u >> e.v >> e.cost)
		{
			edge.push_back(e);
			graph[e.u][e.v] = e.cost;
		}

		dijkstra();
	}
	~DijkstraAndBellmanFord()
	{
		saveFile("dijkstra.txt",0);
		bellmanFord();
		saveFile("bellmanFord.txt", 1);
		cout << "dijkstra.txt文件和bellmanFord.txt保存完成" << endl;
		for (int i = 0; i < size; ++i)
		{
			delete graph[i];
			graph[i] = nullptr;
		}
		delete[] graph;
		graph = nullptr;
	}

private:
	void dijkstra()
	{
		vector<int> visited;
		for (int i = 0; i < size; ++i)
		{
			visited.push_back(0);
			dis.push_back(MAX);
			if (dis[i] < MAX)
				path.push_back(origin);
			else
				path.push_back(-1);
		}
		priority_queue<Node> q;
		dis[origin] = 0;
		Node node{ origin,dis[origin] };
		q.push(node);
		while (!q.empty())
		{
			int v = q.top().v;
			q.pop();
			if (visited[v])
				continue;
			else
				visited[v] = 1;
			for (int i = 0; i < size; ++i)
			{
				if (!visited[i] && dis[v] + graph[v][i] < dis[i])
				{
					dis[i] = dis[v] + graph[v][i];
					path[i] = v;
					Node node{ i,dis[i] };
					q.push(node);
				}
			}
		}
	}
	void saveFile(string filename,int flag)
	{
		fstream out;
		out.open(filename, ios::out);
		char buffer[100];
		vector<char> title(size, 'P');
		for (int i = 0; i < size; ++i)
			title[i] = title[i] - size + i;
		title[origin] = 'S';


		for (int i = 0; i < size; ++i)
		{
			if (i == origin)
				sprintf(buffer, "%c=%.2lf;path=<%s>", title[origin], 0.0, "");
			else
			{
				string pathBuf;
				if(flag == 0)
					getPath(origin, i);
				if (flag == 1)
				{
					vector<int> temp;
					getPath(temp, i);
					reverse(temp.begin(), temp.end());
					shortestPath = temp;
				}
				for (int i = 0; i < shortestPath.size(); ++i)
				{
					pathBuf += title[shortestPath[i]];
					if (i != shortestPath.size() - 1)
						pathBuf += ',';
				}
				sprintf(buffer, "%c=%.2lf;path=<%s>", title[i], dis[i], pathBuf.c_str());
			}
			out << buffer << "\n";
			shortestPath.clear();
		}
		out.close();
	}
	void getPath(int u, int v)
	{
		if (u == v)
		{
			shortestPath.push_back(u);
			return;
		}
		getPath(u, path[v]);
		shortestPath.push_back(v);
	}

	void bellmanFord()
	{
		dis.resize(size);
		path.resize(size);
		fill(dis.begin(), dis.end(), MAX);
		fill(path.begin(), path.end(), origin);
		dis[origin] = 0;
		for (int i = 0; i < size - 1; ++i)
		{
			int ck = 0;
			for (int j = 0; j < edge.size(); ++j)
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

	void getPath(vector<int>& shortestPath, int v)
	{
		while (v != path[v])
		{
			shortestPath.push_back(v);
			v = path[v];
		}
		if (v == path[v])
			shortestPath.push_back(v);
	}

private:
	struct Edge
	{
		int u;
		int v;
		double cost;
	};
	struct Node {
		int v;
		double dis;
		friend bool operator < (const Node& a, const Node& b)
		{
			return a.dis > b.dis;
		}
	};
	vector<double> dis;
	vector<int> path;
	vector<Edge> edge;
	vector<int> shortestPath;
	double **graph;
	int origin;
	int size;
};


int main()
{
	DijkstraAndBellmanFord d;
	return 0;
}
