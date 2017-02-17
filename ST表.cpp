#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <unordered_set>
#include <unordered_map>
using namespace std;

const int MAXN = 1000005;

int pre_cal[MAXN][21];

int main()
{
    int n, a, b, T;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &pre_cal[i][0]);
    }

    T = log2(n);
    int i, dis1, dis2;
    for(int j = 1; j <= T ; j++)
    {
        dis1 = 1<<j, dis2 = 1<<(j - 1);
        for(i = 1; i + dis1 - 1 <= n; i ++)
        {
            pre_cal[i][j] = min(pre_cal[i][j - 1], pre_cal[i + dis2][j - 1]);
        }
    }

    scanf("%d", &n);
    while(n --)
    {
        scanf("%d %d", &a, &b);
        T = log2(b - a + 1);
        printf("%d\n",min(pre_cal[a][T], pre_cal[b - (int)pow(2, T) + 1][T]));
    }

    return 0;
}