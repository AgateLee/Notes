#include <iostream>
#include <cstring>
#include <climits>
#include <algorithm>
using namespace std;

const int SIZE = 1003;
int dp[SIZE][SIZE];
int a[SIZE];
int M, N, S, T, ca;

void dfs()
{
    int cur, need;

    for(int i = 1; i <= N; i ++)
    {
        cur = (a[i] + S - 1) / S;
        for(int j = 0; j <= M; j++)
        {
            for(int k = 0; k <= cur; k++)
            {
                need = a[i] - k * S;
                need = need <= 0 ? 0 : ((need + T - 1) / T);
                dp[i][j + k] = min(dp[i][j + k], dp[i - 1][j] + need);
            }
        }
    }
}

int main()
{
    freopen("input.txt", "r", stdin);
    scanf("%d", &ca);
    while(ca --)
    {
        scanf("%d %d %d %d", &N, &M, &S, &T);
        memset(a, 0, sizeof(a));
        memset(dp, 0, SIZE * sizeof(int));

        for(int i = 1; i <= N; i++)
        {
            scanf("%d", &a[i]);
            fill(dp[i], dp[i] + SIZE, INT_MAX);
        }

        dfs();
        bool flag = true;
        for(int i = 0; i <= M; i++)
        {  
            if(i + dp[N][i] <= M)
            {   
                printf("%d\n", i);
                flag = false;
                break;  
            }
        }  

        if(flag)
            printf("No\n");
    }

    return 0;
}