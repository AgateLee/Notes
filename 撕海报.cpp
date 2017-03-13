#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>
#include <cmath>
#include <stack>
#include <vector>
#include <set>
using namespace std;

const int MAXN = 1005;

class poster{
public:
	int x1, y1, x2, y2;
	bool sign[4];
	set<int> up;

	poster():x1(0), y1(0), x2(0), y2(0){ memset(sign, false, sizeof sign);};
	poster(int a, int b, int c, int d):x1(a), y1(b), x2(c), y2(d){ memset(sign, false, sizeof sign);};
	~poster(){};

	bool inPoster(int x, int y, const poster & p)
	{
		return x < p.x2 && x > p.x1 && y < p.y2 && y > p.y1;
	}

	bool cover(const poster & p)
	{
		return !(x1 >= p.x2 || p.x1 >= x2 || y1 >= p.y2 || p.y1 >= y2);
	}
};

class poster ps[MAXN];

void check(int idx, set<int> & cur, bool vis[MAXN])
{
	if(vis[idx])
		return;

	vis[idx] = true;
	cur.insert(idx);
	for(set<int>::iterator it = ps[idx].up.begin(); it != ps[idx].up.end(); it ++)
	{
		check(* it, cur, vis);
	}
}

int main()
{
	int w, h, n;
	vector<int> st(MAXN);
	st.clear();

	scanf("%d %d %d", &w, &h, &n);
	for(int i = 0; i < n; i++)
	{
		scanf("%d %d %d %d", &ps[i].x1, &ps[i].y1, &ps[i].x2, &ps[i].y2);
	}

	for(int i = 0; i < n; i++)
	{
		poster & t = ps[i];
		for(int j = i + 1; j < n; j++)
		{
			if(!t.sign[0] && t.inPoster(t.x1, t.y1, ps[j]))
				t.sign[0] = true;

			if(!t.sign[1] && t.inPoster(t.x1, t.y2, ps[j]))
				t.sign[1] = true;

			if(!t.sign[2] && t.inPoster(t.x2, t.y1, ps[j]))
				t.sign[2] = true;

			if(!t.sign[3] && t.inPoster(t.x2, t.y2, ps[j]))
				t.sign[3] = true;

			if(t.cover(ps[j]))
				t.up.insert(j);

			if(t.sign[0] && t.sign[1] && t.sign[2] && t.sign[3])
				break;
		}

		if(!t.sign[0] || !t.sign[1] || !t.sign[2] || !t.sign[3])
		{
			st.push_back(i);
		}
	}

	int ans = 0, ans_pos = -1;
	for(int i = 0; i < st.size(); i++)
	{
		set<int> cur;
		bool vis[MAXN] = {false};
		check(st[i], cur, vis);

		if(cur.size() > ans)
		{
			ans = cur.size();
			ans_pos = st[i];
		}
	}

	printf("%d %d\n", ans, ans_pos + 1);

	return 0;
}