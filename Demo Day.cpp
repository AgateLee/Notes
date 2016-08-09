#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int INF = 1000;
const int MAXN = 105;
int grid[MAXN][MAXN];
int up[MAXN][MAXN], l[MAXN][MAXN];

int main()
{
    int n, m;
    char c;
    scanf("%d %d", &n, &m);
    memset(grid, 0, sizeof(grid));
    memset(up, 0, sizeof(up));
    memset(l, 0, sizeof(l));
    for(int i = 1; i <= n; i++)
    {
        getchar();
        for(int j = 1; j <= m; j++)
        {
            scanf("%c", &c);
            if(c == 'b')
                grid[i][j] = 1;

            up[i][j] = INF;
            l[i][j] = INF;
        }
        grid[i][m + 1] = 1;
    }

    for(int j = 1; j <= m; j++)
    {
        grid[n + 1][j] = 1;
    }

    l[1][1] = grid[1][1];
    for(int j = 2; j <= n; j++)
    {
        l[1][j] = l[1][j - 1] + grid[1][j];
    }

    up[1][1] = l[1][1] + ((grid[1][2] == 1) ? 0 : 1);
    for(int i = 2; i <= n; i++)
    {
        up[i][1] = up[i - 1][1] + grid[i][1];
    }

    int a, b, cur;
    for(int i = 2; i <= n; i++)
    {
        for(int j = 2; j <= m; j++)
        {   
            up[i][j] = min(up[i - 1][j], l[i - 1][j] + !grid[i - 1][j + 1])
                + grid[i][j];
            l[i][j] = min(l[i][j - 1], up[i][j - 1] + !grid[i + 1][j - 1])
                + grid[i][j];
        }
    }

    printf("%d\n", min(up[n][m], l[n][m]));

    return 0;
}