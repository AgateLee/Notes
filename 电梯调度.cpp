#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <set>
using namespace std;

const int INF = 10000005;

typedef struct req{
    int t, s, e;
    int id;

    req(){};
    req(int t1, int s1, int e1, int i1):t(t1), s(s1), e(e1), id(i1){};

    bool operator <(const struct req r) const
    {
        return t == r.t ? s < r.s : t < r.t;
    }
} req;

typedef struct ans{
    int t;
    int id;

    ans(){};
    ans(int t1, int id1): t(t1), id(id1) {};

    bool operator <(const struct ans r) const
    {
        return id < r.id;
    }
} ans;

int main()
{   
    int T, N, t, s, e, pos, time, dir;
    freopen("input.txt", "r", stdin);
    cin >> T;
    while(T--)
    {
        cin >> N;
        priority_queue<req> q;
        priority_queue<ans> qa;
        set<int> L;
        set<pair<int, req> > w;
        set<pair<int, req> >::iterator it;
        L.insert(INF);
        L.insert(0);
        w.insert(make_pair(0, req(-INF, -INF, -INF, -INF)));
        w.insert(make_pair(INF, req(INF, INF, INF, INF)));

        for(int i = 0; i < N; i++)
        {
            scanf("%d %d %d", &t, &s, &e);
            q.push(req(-t, s, e, -i));
        }

        pos = time = 1;
        dir = 0; // still
        // cout << "START " << q.size() << endl;
        while((!q.empty() || (w.size()) != 2))
        {
            // cout << "# " << time << " at " << pos << " dir " << dir << " size " << q.size() << " " << w.size() << endl;
            while(!q.empty() && q.top().t == -time)
            {
                req temp = q.top();
                // cout << "Recv " << -temp.t << " : " << temp.s << "->" << temp.e << endl;
                w.insert(make_pair(temp.s, temp));
                L.insert(temp.s);
                q.pop();
            }

            it = w.lower_bound(make_pair(pos, req(-INF, 0, 0, 0)));
            while(it != w.end() && it->first == pos)
            {
                L.insert(it->second.e);
                qa.push(ans(it->second.t + time, it->second.id));
                // cout << "**" << it->second.id << endl;
                it = w.erase(it);
            }

            L.erase(pos);

            int down = * L.lower_bound(1);
            int up = * L.upper_bound(pos);
            
            if(down > pos)
                down = 0;

            switch(dir)
            {
                case 1:
                    dir = up == INF ? (down == 0 ? 0 : -1) : 1;
                    break;
                case 0:
                case -1:
                    dir = down == 0 ? (up == INF ? 0 : 1) : -1;
                    break;
            }

            // cout << "* up " << up << " down " << down << " to " << dir << endl;

            if(dir == 1)
                pos ++;
            else if(dir == -1)
                pos --;

            time ++;
        }

        while(!qa.empty())
        {
            cout << qa.top().t << endl;
            qa.pop();
        }
    }

    return 0;
}