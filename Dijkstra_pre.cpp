#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

const int MAXN = 1005;
const int INF = 1e6;

struct Edge{
	int from, to, dist;
};

struct HeapNode{
	int u, d;
	bool operator < (const HeapNode & t) const
	{
		return d > t.d;
	}
};

struct Dijkstra{
	int n, m;
	vector<Edge> edges;
	vector<int> G[MAXN];
	bool vis[MAXN];
	int d[MAXN];
	int pre[MAXN];

	void init(int n) {
		this->n = n;
		for(int i = 1; i <= n; i++)
			G[i].clear();
		edges.clear();
	}

	void addEdge(int from, int to, int dist)
	{
		edges.push_back((Edge){from, to, dist});
		m = edges.size();
		G[from].push_back(m - 1);
	}

	void dijkstra(int s) {
		priority_queue<HeapNode> Q;

		for(int i = 1; i <= n; i++)
			d[i] = INF;
		d[s] = 0;

		memset(vis, false, sizeof(vis));
		memset(pre, -1, sizeof(pre));

		Q.push((HeapNode){s, 0});
		while(!Q.empty())
		{
			HeapNode x = Q.top();
			Q.pop();
			int u = x.u;
			if(vis[u]) continue;
			vis[u] = true;

			for(int i = 0; i < (int)G[u].size(); i++)
			{
				Edge & e = edges[G[u][i]];

				if(d[e.to] > d[u] + e.dist)
				{
					d[e.to] = d[u] + e.dist;
					pre[e.to] = e.from;
					Q.push((HeapNode){e.to, d[e.to]});
				}
			}
		}
	}

	vector<int> getPath(int t)
	{
		vector<int> path;
		for(; t != -1; t = pre[t])
		{
			path.push_back(t);
		}

		reverse(path.begin(), path.end());
		return path;
	}
} dij;

int main()
{
	int n, m, s, t, a, b, c;
	scanf("%d %d %d %d", &n, &m, &s, &t);

	dij.init(n);
	while(m --)
	{
		scanf("%d %d %d", &a, &b, &c);
		dij.addEdge(a, b, c);
		dij.addEdge(b, a, c);
	}

	dij.dijkstra(s);

	printf("%d\n", dij.d[t]);
	return 0;
}

