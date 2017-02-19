#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <cstring>
using namespace std;

int ca, n, m, t, s;
int ck, cj;
int fk[1002], fj[1002];

struct Node{
	int pos, val;

	Node(){pos = val = 0;};
} eq[16];

bool cmp(const Node & a, const Node & b)
{
	return a.val > b.val;
}

void solve()
{
	int ans = -1, n2 = n - 1, total = m * n;
	int guess = 1<<total, cs, uk, uj, cur;
	bool sign2 = false;
	bool sign[4] = {false};

	// guess恰好大于所有 m * n 位二进制数
	// cur 记录当前的对舰输出能力， cs 记录当前对空能力
	// uk、uj记录当前使用到的对空、对舰飞机序号
	for(int g = 0; g < guess; g++)
	{
		cur = cs = uj = uk = 0;
		memset(sign, false, sizeof(sign));

		for(int i = 0; i < total; i++)
		{
			if(g&(1<<i) && uj < cj) // 为1的位装备对舰飞机
			{
				cur += eq[i].val * fj[uj];
				sign[eq[i].pos] = true;
				uj ++;
			}
			else if(uk < ck)
			{
				cs += eq[i].val * fk[uk];
				uk ++;
			} 
		}

		// 更新结果
		if(cs >= s && ans <= cur) 
		{
			// cout <<cs << " " << cur << " " << g << " " << sign[0] << sign[1] << sign[2] << sign[3] << endl;
			if(sign[0] && sign[min(1, n2)] && sign[min(2, n2)] && sign[min(3, n2)])
				sign2 = true;
			else if(cur > ans)
				sign2 = false;
			ans = cur;
		}
	}

	if(ans >= 0)
	{
		printf("%d\n", ans);
		sign2 ? printf("Yes\n") : printf("No\n");
	}
	else printf("Not Exist\n");
}

int main()
{
	scanf("%d", &ca);
	while(ca --)
	{
		scanf("%d %d %d %d", &n, &m, &t, &s);
		memset(eq, 0, sizeof(eq));
		memset(fk, 0, sizeof(fk));
		memset(fj, 0, sizeof(fj));

		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < m; j++)
			{
				scanf("%d", &eq[i * m + j].val);
				eq[i * m + j].pos = i;
			}
		}
		sort(eq, eq + n * m, cmp);

		ck = 0, cj = 0;
		for(int i = 0; i < t; i++)
		{
			scanf("%d", &fk[i]);
			if(fk[i]) ck++;
		}

		for(int i = 0; i < t; i++)
		{
			scanf("%d", &fj[i]);
			if(fj[i]) cj++;
		}
		sort(fk, fk + t, greater<int>());
		sort(fj, fj + t, greater<int>());

		solve();
	}
}