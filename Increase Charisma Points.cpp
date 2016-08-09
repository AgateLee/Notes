#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

const int INF = 1<<30;
const int MAXN = 102;
long long dis[MAXN];
long long edge[MAXN][MAXN][32];

void calEdge(int n, int up)
{
    for(int p = 1; p <= up; p++)
    {
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                for(int k = 0; k < n; k++)
                {
                    if(edge[i][k][p - 1] != 0 && edge[k][j][p - 1] != 0 
                        && (edge[i][j][p] == 0 ||
                        edge[i][j][p] > edge[i][k][p - 1] + edge[k][j][p - 1]))
                    {
                        edge[i][j][p] = edge[i][k][p - 1] + edge[k][j][p - 1];
                    }
                }
            }
        }
    }
}

int main()
{
    int N, M, ans = 0, up = 0;
    // freopen("input.txt", "r", stdin);
    scanf("%d %d", &N, &M);
    up = log2(M) + 1;

    memset(edge, 0, sizeof(edge));
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            scanf("%lld", &edge[i][j][0]);
        }
    }

    calEdge(N, up);

    long long newdis[MAXN];
    bool flag = false;
    memset(dis, 0, sizeof(dis));
    for(int p = up; p >= 0; p--)
    {
        flag = false;
        fill(newdis, newdis + MAXN, INF);
        for(int i = 0; i < N; i++)
        {
            for(int j = 0; j < N; j++)
            {
                if(edge[i][j][p] != 0 && newdis[i] > dis[j] + edge[j][i][p])
                {
                    newdis[i] = dis[j] + edge[j][i][p];

                    if(newdis[i] <= M)
                    {
                        flag = true;
                    }
                }
            }
        }

        if(flag)
        {
            memcpy(dis, newdis, sizeof(dis));
            ans = ans + (1<<p);
        }
    }

    printf("%d\n", ans);

    return 0;
}