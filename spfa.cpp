#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

const int MAXN = 100005;
const int INF = 1e6;

struct Edge{
	int from, to, dist;

	Edge(){};
	Edge(int f, int t, int d):from(f), to(t), dist(d){};
};

vector<int> G[MAXN];
vector<Edge> edges;

int myRank[MAXN], dis[MAXN];
bool inque[MAXN];

void init(int n)
{
	for(int i = 0; i <= n; i++)
		G[i].clear();
	edges.clear();
}

void add(int u, int v, int w)
{
	edges.push_back(Edge(u, v, w));
	int m = edges.size();
	G[u].push_back(m - 1);
}

int spfa(int s, int n)
{
	for(int i = 0; i <= n; i++)
	{
		dis[i] = INF;
		myRank[i] = 0;
		inque[i] = false;
	}

	dis[s] = 0;
	myRank[s] = 1;
	queue<int> que;
	inque[s] = true;
	que.push(s);

	while(!que.empty())
	{
		int u = que.front();
		inque[u] = false;
		que.pop();

		for(int i = 0; i < (int)G[u].size(); i++)
		{
			Edge e = edges[G[u][i]];
			if(dis[e.to] > dis[u] + e.dist)
			{
				dis[e.to] = dis[u] + e.dist;
				if(!inque[e.to])
				{
					que.push(e.to);
					inque[e.to] = true;
					myRank[e.to] ++;
					if(myRank[e.to] >= n) return false;
				}
			}
		}
	}

	return true;
}

int main()
{
	int n, m, s, t, a, b, c;

	scanf("%d %d %d %d", &n, &m, &s, &t);
	init(n);
	while(m --)
	{
		scanf("%d %d %d", &a, &b, &c);
		add(a, b, c);
		add(b, a, c);
	}

	spfa(s, n);

	printf("%d\n", dis[t]);

	return 0;
}