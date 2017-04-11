#include <iostream>
#include <cstring>
#include <cctype>
#include <cstdio>
#include <string>
#include <cmath>
#include <stack>
#include <queue>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#define LL long long
using namespace std;
  
const int MAXN = 1005;
const int INF = 0x3F3F3F3F;
const double eps = 1e-6;
const int MOD = 1e9 + 7;

int arr[MAXN];

typedef struct node{
	int x, y;
	
	bool operator < (const node & t) const
	{
		return x == t.x ? y < t.y : x < t.x;
	}
	
	node operator + (int p)
	{
		node t;
		t.x = x;
		t.y = y;
		
		if(t.y + p < arr[x])
			t.y += p;
		else
		{
			t.y = 0;
			t.x ++;
		}
		
		return t;
	}
	
	void max(node t1, node t2)
	{
		if(t1 < t2)
		{
			x = t2.x;
			y = t2.y;
		}
		else
		{
			x = t1.x;
			y = t1.y;
		}
	}
} node;

node g[MAXN][MAXN];

int main()
{
	#ifndef ONLINE_JUDGE
		freopen("1.txt", "r", stdin);
	#endif
 
	int ca, n, m, s, t, need;

	scanf("%d", &ca);
	while(ca --)
	{
		scanf("%d%d%d%d",&n, &m, &s, &t);
		memset(g, 0, sizeof(g));
		memset(arr, INF, sizeof(arr));
		for(int i = 0; i < n; i++)
		{
			scanf("%d", &arr[i]);
		}
		
		int ans = 0, point = 0;
		bool flag = true;
		for(int i = 0; i <= m; i++)
		{
			for(int j = 0; j <= m - i; j++)
			{
				if(i && j)
					g[i][j].max(g[i - 1][j] + t, g[i][j - 1] + s);
				else if(i)
					g[i][j].max(g[i - 1][j] + t, g[i][j]);
				else if(j)
					g[i][j].max(g[i][j - 1] + s, g[i][j]);
					
				if(g[i][j].x == n)
				{
					if(!ans || j < ans || (j == ans && g[i][j].y < point))
					{
						ans = j;
						point = g[i][j].y;
						flag = false;
					}
				}
				
//				printf("%d %d: %d %d\n", i, j, g[i][j].x, g[i][j].y);
			}
		}
		
		if(flag)
			printf("No\n");
		else 
			printf("%d\n",ans);
	}
	
	return 0;
}