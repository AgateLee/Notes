#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>
#include <cmath>
#include <stack>
#include <queue>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
using namespace std;

const int MAXN = 100005;
const int INF = 0x3F3F3F3F;
const double eps = 1e-6;

vector<int> num;
map<int, int> p;

int main()
{
	int n, a;

	#ifndef ONLINE_JUDGE
		freopen("1.txt", "r", stdin);
	#endif

	while(scanf("%d", &n) != EOF)
	{
		vector<string> ans;

		string s(n, '0');
		int r = n - 1, sum = 1<<n, st;

		// cout << s << endl;
		ans.push_back(s);
		sum --;

		while(sum)
		{
			if(s[r] == '1')
				s[r] = '0';
			else
				s[r] = '1';
			// cout << s << endl;
			ans.push_back(s);
			sum --;

			for(st = r; s[st] != '1'; st --);
			st --;

			if(st >= 0)
			{
				if(s[st] == '1')
					s[st] = '0';
				else
					s[st] = '1';

				// cout << s << endl;
				ans.push_back(s);
				st --;
				sum --;
			}
		}
	}

	return 0;
}
