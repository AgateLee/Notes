#include <iostream>
#include <map>
#include <set>
using namespace std;
const int INF = 1<<30;

typedef struct node{
    int st, ed;

    node(const int s, const int e):st(s), ed(e){};
    bool operator < (const node a) const
    {
        return st == a.st ? ed < a.ed : st < a.st;
    }
} node, * pnode;

map<int, int> ans;
set<pair<node, int> > data;

void show()
{
    set<pair<node, int> >::iterator it;

    for(it = data.begin(); it != data.end(); it++)
    {
        if(it->first.st >= 0 && it->first.ed < INF)
            printf("%d~%d:%d, ", it->first.st, it->first.ed, it->second);
    }
    printf("\n");
}

int main()
{
    int n, m, need, pos = -1, ear = 1;
    scanf("%d %d", &n, &m);

    ans.clear();
    data.clear();
    data.insert(make_pair(node(-INF, 0), -INF));
    data.insert(make_pair(node(m, INF), INF));

    map<int, int>::iterator ita;
    set<pair<node, int> >::iterator it, it2;

    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &need);
        bool finding = true;
        pos = need - 1;

        it = data.upper_bound(make_pair(node(pos, 0), 0));

        while(finding)
        {
            // show();
            // printf("Search: %d\n", pos);
            if(it == data.end())
            {
                for(it = data.begin(); it != data.end(); it++)
                {
                    if(it->second == ear)
                    {
                        it2 = it;
                        it --;
                        pos = it->first.ed - 1 + need;
                        data.erase(it2);
                        ear ++;
                        break;
                    }
                }
            }
            else
            {
                it2 = it;
                it --;

                if(it2->first.st - it->first.ed >= need)
                {
                    data.insert(make_pair(node(it->first.ed, it->first.ed + need), i));
                    finding = false;
                }
                else
                {
                    pos = it2->first.ed - 1 + need;
                }
            }

            it = data.upper_bound(make_pair(node(pos, 0), 0));
        }
        // show();
    }

    for(it = data.begin(); it != data.end(); it ++)
    {
        if(it->first.st >= 0 && it->first.ed < INF)
            ans.insert(pair<int, int>(it->second, it->first.st));
    }

    for(ita = ans.begin(); ita != ans.end(); ita ++)
    {
        printf("%d %d\n", ita->first, ita->second);
    }

    return 0; 
}  