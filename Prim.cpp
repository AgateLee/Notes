#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

const int MAXV = 1005;
const int INF = 1e6;

int cost[MAXV][MAXV];
int minc[MAXV];
bool used[MAXV];
int n;

int prim()
{
	fill(minc, minc + n, INF);
	memset(used, 0, sizeof(used));

	minc[0] = 0;
	int res = 0;

	while(true)
	{
		int v = -1;

		for(int i = 0; i < n; i++)
		{
			if(!used[i] && (v == -1 || minc[i] < minc[v]))
				v = i;
		}

		if(v == -1) break;
		used[v] = true;

		res += minc[v];
		for(int i = 0; i < n; i++)
		{
			minc[i] = min(minc[i], cost[v][i]);
		}
	}

	return res;
}

int main()
{
	scanf("%d", &n);

	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			scanf("%d", &cost[i][j]);

	printf("%d\n", prim());

	return 0;
 }