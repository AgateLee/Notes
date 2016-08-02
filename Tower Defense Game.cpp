#include <iostream>
#include <cstring>
#include <algorithm>
#include <set>
#include <queue>
using namespace std;

const int MONEY = 200000000;

typedef struct node{
    int p, q, pt, qt;
    node * left, * right;

    node()
    {
        p = q = pt = qt = 0;
        left = right = NULL;
    }
} node, * pnode;

node tree[10002];
set<int> path[10002];

void sortByQt(pnode p)
{
    pnode son = p->left;

    if(son == NULL)
        return;

    pnode head, add, pre, cur;

    head = new node;
    head->right = son;
    add = son->right;
    son->right = NULL;

    while(add)
    {
        pre = head;
        cur = pre->right;

        while(cur && add->qt < cur->qt)
        {
            pre = cur;
            cur = pre->right;
        }

        pre->right = add;
        add = add->right;
        pre->right->right = cur;
    }

    p->left = head->right;
    delete head;
}

void dfs(pnode p)
{
    int wallet = MONEY;
    int minWallet = MONEY;

    pnode son = p->left;
    while(son)
    {
        dfs(son);
        son = son->right;
    }

    sortByQt(p);

    wallet -= p->p;
    if(minWallet > wallet)
        minWallet = wallet;
    wallet += p->q;

    son = p->left;
    while(son)
    {
        wallet -= son->pt;
        if(minWallet > wallet)
            minWallet = wallet;
        wallet += son->qt;
        son = son->right;
    }

    p->pt = MONEY - minWallet;
    p->qt = wallet - minWallet;
}

int main()
{
    int N, pos = 1, a, b;
    scanf("%d", &N);

    for(int i = 1; i <= N; i ++)
    {
        scanf("%d %d", &tree[pos].p, &tree[pos].q);
        pos ++;
    }

    set<int>::iterator it, it2;

    for(int i = 1; i < N; i++)
    {
        scanf("%d %d", &a, &b);

        path[a].insert(b);
        path[b].insert(a);
    }

    int st, cur;
    queue<int> que;
    que.push(1);

    while(que.size() > 0)
    {
        st = que.front();
        que.pop();

        for(it = path[st].begin(); it != path[st].end(); it ++)
        {
            if(tree[st].left == NULL)
            {
                tree[st].left = &tree[* it];
                cur = * it;
            }
            else
            {
                tree[cur].right = &tree[* it];
                cur = * it;
            }

            que.push(cur);
            
            it2 = path[cur].find(st);
            path[cur].erase(it2);
        }
    }

    dfs(&tree[1]);

    printf("%d\n", tree[1].pt);

    return 0;
}