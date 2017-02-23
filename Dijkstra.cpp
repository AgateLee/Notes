#include <iostream>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

const int MAXN = 1e6;

int path[1005][1005];
int d[1005];
bool vis[1005];
int n, m, s, t;

int main()
{
	int a, b, c, pos;

	scanf("%d %d %d %d", &n, &m, &s, &t);

	for(int i = 1; i <= n; i ++)
	{
		fill(path[i], path[i] + n + 1, MAXN);
		path[i][i] = 0;
		d[i] = MAXN;
	}

	for(int i = 0; i < m; i ++)
	{
		scanf("%d %d %d", &a, &b, &c);
		path[a][b] = min(path[a][b], c);
		path[b][a] = min(path[b][a], c);
		if(a == s) d[b] = min(d[b], c);
		else if(b == s) d[a] = min(d[a], c);
	}

	memset(vis, 0, sizeof(vis));
	d[s] = 0;
	vis[s] = 1;
	
	while(true)
	{
		pos = -1;

		for(int i = 1; i <= n; i++)
		{
			if(vis[i]) continue;
			if(pos == -1 || d[pos] > d[i])
				pos = i;
		}
		
		if(pos == -1) break;
		vis[pos] = true;
		for(int i = 1; i <= n; i++)
		{
			d[i] = min(d[i], d[pos] + path[pos][i]);
		}
	}

	printf("%d\n", d[t]);

	return 0;
}