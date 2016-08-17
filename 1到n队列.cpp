#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int maxn = 100000;
int arr[maxn + 2];
int next[maxn + 2];
int pre[maxn + 2];

void check(int n)
{
	queue<int> q;
	
	for(int i = 1; i <= n; i++)
	{
		q.push(arr[i]);
	}
	
	while(!q.empty())
	{
		int x = q.front();
		q.pop();
		q.push(x);
		x = q.front();
		printf("%d ", x);
		q.pop();
	}
}

int main()
{
	int n, T;
	scanf("%d", &T);
	
	while(T --)
	{
		scanf("%d", &n);
		
		if(n == 1)
		{
			printf("1\n");
			continue;
		}
		
		for(int i = 1; i < n; i++)
		{
			next[i] = i + 1;
			pre[i] = i - 1;
		}
		next[n] = 1;
		pre[n] = n - 1;
		pre[1] = n;
		
		int cur = 1, pos = 2, temp;
		
		while(cur <= n)
		{
			arr[pos] = cur ++;
			temp = pre[pos];
			next[temp] = next[pos];
			pre[next[pos]] = temp;
			pos = next[next[pos]];
		}
		
		for(int i = 1; i <= n; i++)
		{
			printf("%d ", arr[i]);
		}
		
//		printf("\ncheck: ");
//		check(n);
	}
	
	return 0;
}