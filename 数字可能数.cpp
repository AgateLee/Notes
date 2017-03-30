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

const int MAXN = 20;
const int INF = 0x3F3F3F3F;
const double eps = 1e-6;
const int MOD = 1e9 + 7;

char num1[MAXN], num2[MAXN];
int fa[36];

void init()
{
	for(int i = 0; i < 10; i++)
		fa[i] = i;
	for(int i = 10; i < 36; i++)
		fa[i] = -1;
}

int find(int a)
{	
	while(fa[a] != a)
		a = fa[a];
	return fa[a];
}

bool merge(int a, int b)
{
	if(fa[a] == -1)
		fa[a] = a;
	if(fa[b] == -1)
		fa[b] = b;
	
	int pa = find(a);
	int pb = find(b);
	
	if(pa < 10 && pb < 10)
		return pa == pb;
	else if(pa < 10)
	{
		fa[pb] = pa;
		fa[a] = fa[b] = pa;
	}
	else if(pb < 10)
	{
		fa[pa] = pb;
		fa[a] = fa[b] = pb;
	}
	else
	{
		fa[pa] = min(pa, pb);
		fa[pb] = fa[a] = fa[b] = fa[pa];
	}
//	cout << "merge " << a << " " << b << " " << fa[pa] << endl;
	return true;
}

int main()
{
	#ifndef ONLINE_JUDGE
		freopen("1.txt", "r", stdin);
	#endif
	
	int t, n;
	string s1, s2;
	scanf("%d", &t);
	while(t --)
	{
		scanf("%d", &n);
		scanf("%s", num1);
		scanf("%s", num2);
		
		bool flag = true;
		init();
		for(int i = 0; i < n && flag; i++)
		{
			int a, b;
			
			if(isalpha(num1[i]))
				a = num1[i] - 'A' + 10;
			else 
				a = num1[i] - '0';
				
			if(isalpha(num2[i]))
				b = num2[i] - 'A' + 10;
			else 
				b = num2[i] - '0';
				
			if(!merge(a, b))
				flag = false;
		}
		
		int first = -1, sum = 1;
		
		if(isalpha(num1[0]))
			first = find(num1[0] - 'A' + 10);
		else if(isalpha(num2[0]))
			first = find(num2[0] - 'A' + 10);
		else 
			first = min(num1[0] - '0', num2[0] - '0');
			
		if(first == 0)
			flag = false;
			
		if(flag)
		{
			set<int> gp;
			
			for(int i = 10; i < 36; i++)
			{
//				cout << fa[i] << " ";
				int f = find(i);
				if(f >= 10)
					gp.insert(f);
			}
//			cout << gp.size() << endl;
			for(set<int>::iterator it = gp.begin(); it != gp.end(); it++)
			{
				if(first == * it)
					sum *= 9;
				else 
					sum *= 10;
			}
			
			printf("%d\n", sum);
		}
		else 
			printf("0\n");
	}
	return 0;
}
