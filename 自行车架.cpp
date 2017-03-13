#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>
#include <cmath>
#include <stack>
#include <vector>
#include <set>
using namespace std;

const int MAXN = 55;
const int INF = 0x3f3f3f3f;

int f[MAXN][MAXN][MAXN][4][4][4];

int main()
{
	memset(f, INF, sizeof(f));

	f[0][0][0][0][0][1] = 0;
	f[1][0][0][0][0][3] = 1;
	f[0][1][0][1][0][3] = 1;
	f[0][0][1][2][0][3] = 1;

	for(int i = 0; i <= 50; i++)
	for(int j = 0; j <= 50; j++)
	for(int k = 0; k <= 50; k++)
		for(int x = 0; x < 3; x++)
		for(int y = 0; y < 3; y++)
		for(int d = 1; d <= 3; d++)
		{
			if(f[i][j][k][x][y][d] != INF)
			{
				for(int ad = 0; ad < 3; ad++)
				{
					int fi = i, fj = j, fk = k;
					if(ad == 0) fi++;
					else if(ad == 1) fj++;
					else if(ad == 2) fk++;

					int fd = d + max(x, ad) + 2;
					if(fd > 3) fd = 3;
					f[fi][fj][fk][ad][y][fd] = min(f[fi][fj][fk][ad][y][fd], 
						f[i][j][k][x][y][d] + max(x, ad) + 2);

					fd = max(max(y, ad) + 2 - d, 1);
					// if(fd > 3) fd = 3;
					f[fi][fj][fk][ad][x][fd] = min(f[fi][fj][fk][ad][x][fd],
						f[i][j][k][x][y][d] + fd);
				}
			}
		}
	
	int a, b, c, ans, n;
	scanf("%d", &n);
	while(n --)
	{
		scanf("%d %d %d", &a, &b, &c);
		ans = INF;
	 	for(int x = 0; x < 3; x++)
		for(int y = 0; y < 3; y++)
		for(int d = 1; d <= 3; d++)
		{
			ans = min(ans, f[a][b][c][x][y][d]);
		}

		printf("%d\n", ans);
	}
}