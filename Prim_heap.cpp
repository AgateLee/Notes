#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

const int MAXV = 100005;
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

vector<Edge> es;
vector<int> G[MAXV];
bool used[MAXV];
int n, m;

void init(int n, int m) 
{
    for(int i = 1; i <= n; i++)
        G[i].clear();
    es.reserve(m<<1);
    es.clear();
}

void addEdge(int from, int to, int dist)
{
    es.push_back((Edge){from, to, dist});
    int sz = es.size();
    G[from].push_back(sz - 1);
}

int prim()
{
	memset(used, false, sizeof(used));
	int res = 0;

	priority_queue<HeapNode> que;
	que.push((HeapNode){1, 0});
	while(true)
	{
		HeapNode x;
		int u = 1;

		do
		{
			x = que.top();
			que.pop();
			u = x.u;
		} while(used[x.u] && !que.empty());

		if(used[u]) break;
		used[u] = true;

		res += x.d;
		for(int i = 0; i < G[u].size(); i++)
		{
			Edge e = es[G[u][i]];
			que.push((HeapNode){e.to, e.dist});
		}
	}

	return res;
}


int main()
{
	scanf("%d %d", &n, &m);
	
	init(n, m + 1);

	int a, b, c;
	while(m --)
	{
		scanf("%d %d %d", &a, &b, &c);
		addEdge(a, b, c);
		addEdge(b, a, c);
	}

	printf("%d\n", prim());

	return 0;
 }