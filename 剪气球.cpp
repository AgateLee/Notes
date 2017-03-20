#include <iostream>
#include <thread>
#include <cstring>
#include <cstdio>
#include <string>
#include <cmath>
#include <stack>
#include <vector>
#include <set>
using namespace std;

const int MAXN = 100005;
const int INF = 0x3f3f3f3f;
const int MOD = 1000000007;

int sum[MAXN], arr[MAXN], num[10];

int main()
{
	int n, a;
	
	scanf("%d", &n);
	memset(sum, 0, sizeof(sum));

	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &arr[i]);

		memset(num, 0, sizeof(num));
		num[arr[i]] ++;
		sum[i] = sum[i - 1];
		for(int j = i - 1; j >= 0; j--)
		{
			num[arr[j]] ++;
			if(num[arr[j]] > 1)
				break;

			if (j == 0)
				sum[i]++;
			else 		
				sum[i]=(sum[i] + sum[j-1]) % MOD;
		}
	}

	printf("%d\n", sum[n]);

	return 0;
}