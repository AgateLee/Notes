#include <iostream>
#include <cstring>
#include <cmath>
#include <stack>
#include <queue>
#include <vector>
using namespace std;

const int MAXN = 100002;

vector<int> tree[MAXN];
int h[MAXN], h2[MAXN], len = 0;
bool vis[MAXN];

int dfs(int pos)
{
	int m = tree[pos].size();
	int ans = 0, ans2 = 0, temp;

	if(m)
	{
		for(int i = 0; i < m; i++)
		{
			if(!vis[tree[pos][i]])
			{
				vis[tree[pos][i]] = true;
				temp = dfs(tree[pos][i]);
				if(ans <= temp)
				{
					ans2 = ans;
					ans = temp;
				}
				else if(ans2 <= temp)
				{
					ans2 = temp;
				}
			}
		}
		h[pos] = ans + 1;
		h2[pos] = ans2;
	}
	else
	{
		h[pos] = 1;
	}

	return h[pos];
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
	memset(h, 0, sizeof(h));
	memset(h2, 0, sizeof(h2));

	for(int i = 1; i <= n; i++)
	{
		if(!vis[i])
		{
			vis[i] = true;
			h[i] = dfs(i);
		}

		// cout << i << " " << h[i] << " " << h2[i] << endl;
		len = max(len, h[i] + h2[i] - 1);
	}

	printf("%d\n", len);

	return 0;
}