#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

typedef struct mypair{
	int v, w;
	
	mypair(int v1, int w1): v(v1), w(w1){};
} mypair;

const int maxn = 100100;

int root = 1, N, M;
int level[maxn], node[maxn], path[maxn];
long long total = 0;
vector<mypair> len[maxn];

void init()
{
	memset(level, 0, sizeof(level));
	memset(node, 0, sizeof(node));
	memset(path, 0, sizeof(path));
	
	total = 0;
	root = 1;
	level[root] = 1;
}

void dfs(int r)
{
	node[r] = 1;
	
	for(int i = 0; i < len[r].size(); i++)
	{
		int v = len[r][i].v, w = len[r][i].w;
		
		if(level[v] == 0)
		{
			level[v] = level[r] + 1;
			path[v] = w;
			dfs(v);
			node[r] += node[v];
			total += (long long)w * node[v] * (N - node[v]);
		}
	}
}

void change(int a, int b, int c)
{
	if(level[a] < level[b])
	{
		a ^= b;
		b ^= a;
		a ^= b;
	}
	
	int del = c - path[a];
	
	total += (long long)del * node[a] * (N - node[a]);
	path[a] = c;
}

int main()
{
	init();
	
	int a, b, c;
	char op[32];
	
	scanf("%d %d", &N, &M);
	
	for(int i = 1; i < N; i++)
	{
		scanf("%d %d %d", &a, &b, &c);
		len[a].push_back(mypair(b, c));
		len[b].push_back(mypair(a, c));
	}
	
	dfs(root);
	
	for(int i = 0; i < M; i++)
	{
		scanf("%s", op);
		
		if(op[0] == 'Q')
			printf("%lld\n", total);
		else
		{
			 scanf("%d %d %d", &a, &b, &c);
			 change(a, b, c);
		}
	}
	
	return 0;
}