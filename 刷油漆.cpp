#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
using namespace std;

typedef struct node{
    int id;

    struct node * l, * r;

    node(){};
    node(int i): id(i), l(NULL), r(NULL) {};
} node, * pnode;

int n, m, v[102], dp[102][102], ans = 0;
vector<int> e[102];
bool vis[102];

void insert(pnode r)
{
    // cout << "check " << r->id << endl;
    if(!vis[r->id] && e[r->id].size())
    {
        vis[r->id] = true;
        bool first = true;
        pnode p;
        for(int i = 0; i < e[r->id].size(); i++)
        {
            if(vis[e[r->id][i]])
            {
                // cout << "jump " << r->id << "-" << e[r->id][i] << endl;
                continue;
            }
            // cout << "add " << r->id << "-" << e[r->id][i] << endl;
            if(first)
            {
                r->l = new node(e[r->id][i]);
                p = r->l;
                insert(p);
                first = false;
            }
            else
            {
                p->r = new node(e[r->id][i]);
                p = p->r;
                insert(p);
            }
        }
    }
}

void show(pnode r)
{
    printf("%d ", r->id);
    if(r->l)
        show(r->l);
    if(r->r)
        show(r->r);
}

void cal(pnode r)
{
    if(r->l)
        cal(r->l);

    if(r->r)
        cal(r->r);

    int id = r->id;
    pnode p = r->l;

    while(p)
    {
        for(int i = m; i > 1; i--)
        {
            for(int j = 1; j < i; j ++)
            {
                dp[id][i] = max(dp[id][i], dp[id][i - j] + dp[p->id][j]);
            }
        }

        p = p->r;
    }
}

int main()
{
    int a, b;

    scanf("%d %d", &n, &m);
    memset(v, 0, sizeof(v));
    memset(dp, 0, sizeof(dp));
    memset(vis, 0, sizeof(vis));

    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &v[i]);
        dp[i][1] = v[i];
    }

    for(int i = 1; i < n; i ++)
    {
        scanf("%d %d", &a, &b);
        e[a].push_back(b);
        e[b].push_back(a);
    }

    pnode root = new node(1);
    insert(root);
    cal(root);
    printf("%d\n", dp[1][m]);

    return 0;
}