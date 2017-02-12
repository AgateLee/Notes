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

const int INF = 1<<30;

int A[105], B[105];
int dp[10005];
int Q, N, M, K, T;

int cal()
{
    fill(dp, dp + K + 2, INF);
    dp[0] = 0;

    int x;
    for(int i = 1; i <= M; i++)
    {
        for(int j = 0; j <= K; j ++)
        {
            x = j + B[i];
            dp[min(K, x)] = min(dp[min(K, x)], dp[j] + A[i]);
        }

        B[i] /= T;
    }

    return dp[K];
}

int main()
{
    memset(A, 0, sizeof(A));
    memset(B, 0, sizeof(B));

    cin >> Q;
    while(Q --)
    {
        cin >> N >> M >> K >> T;
        for(int i = 1; i <= M; i++)
            cin >> A[i];
        for(int i = 1; i <= M; i++)
            cin >> B[i];

        long long ans = 0;
        bool flag = true;
        for(int i = 0; i < N; i++)
        {
            ans += cal();
            if(ans > INF)
            {
                flag = false;
                break;
            }
        }

        if(flag) cout << ans << endl;
        else cout << "No Answer" << endl;
    }

    return 0;
}