#include <iostream>
#include <cstring>
#include <cmath>
#include <stack>
#include <queue>
#include <vector>
using namespace std;

const int MAXN = 100002;

vector<int> tree[MAXN];
int len = 0, far;
bool vis[MAXN];

void dfs(int pos, int level)
{
	int m = tree[pos].size();

	if(m)
	{
		if(level > len)
		{
			far = pos;
			len = level;
		}

		for(int i = 0; i < m; i ++)
		{
			if(!vis[tree[pos][i]])
			{
				vis[tree[pos][i]] = true;
				dfs(tree[pos][i], level + 1);
			}
		}
	}
}

int main()
{
	int n, a, b, total = 0;
	
	scanf("%d", &n);
	for(int i = 1; i < n; i++)
	{
		scanf("%d %d", &a, &b);
		tree[a].push_back(b);
		tree[b].push_back(a);
	}

	memset(vis, 0, sizeof(vis));
	vis[1] = true;
	dfs(1, 0);
	
	memset(vis, 0, sizeof(vis));
	vis[far] = true;
	len  = 0;
	dfs(far, 0);

	printf("%d\n", len);

	return 0;
}