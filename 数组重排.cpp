#include <iostream>
#include <cstring>
using namespace std;

int P[101], T[101];

long long gcd(long long a, long long b)
{
    return b == 0 ? a : gcd(b, a % b);
}

long long lcm(long long a, long long b)
{
    return a * b / gcd(a,b);
}

int main()
{
    int n, cur, count;
    long long ans;
    scanf("%d", &n);

    for(long long i = 1; i <= n; i++)
    {
        scanf("%d", &P[i]);
        T[i] = i;
    }

    for(long long i = 1; i <= n; i++)
    {
        cur = i;
        count = 1;

        while(P[cur] != i)
        {
            cur = P[cur];
            count ++;
        }

        T[i] = count;
    }

    ans = T[1];

    for(int i = 2; i <= n; i++)
    {
        ans = lcm(ans, T[i]);
    }

    printf("%lld\n", ans);

    return 0;
}