#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

const int MAXN = 1e6;

int dis[105][105];

int main()
{
	int n, m, a, b, c;

	scanf("%d %d", &n, &m);

	for(int i = 1; i <= n; i++)
	{
		fill(dis[i], dis[i] + n + 1, MAXN);
		dis[i][i] = 0;
	}

	while(m --)
	{
		scanf("%d %d %d", &a, &b, &c);
		dis[a][b] = min(dis[a][b], c);
		dis[b][a] = min(dis[b][a], c);
	}

	for(int k = 1; k <= n; k++)
	{
		for(int i = 1; i <= n; i++)
		{
			if(i == k) continue;
			for(int j = 1; j <= n; j++)
			{
				if(i == j || k == j) continue;
				dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
			}
		}
	}

	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j<= n; j++)
			printf("%d ", dis[i][j]);
		printf("\n");
	}

	return 0;

}