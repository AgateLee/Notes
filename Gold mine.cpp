#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
using namespace std;

const int MAXN = 15005;
const int OFFSET = 30000;

typedef struct point{
    int x, y;

    bool operator < (point t) const
    {
        return x == t.x ? y < t.y : x < t.x;
    }
} point;

typedef struct node{
    int key, val, sum, mx;
    struct node * left;
    struct node * right;
} node, * pnode;

point mine[MAXN];
pnode root = NULL;

void Update(pnode & T)
{
    if(T == NULL)
        return;

    int ls = 0, rs = 0, lmx = 0, rmx = 0;

    if(T->left)
    {
        ls = T->left->sum;
        lmx = T->left->mx;
    }

    if(T->right)
    { 
        rs = T->right->sum;
        rmx = T->right->mx;
    }

    T->sum = ls + T->val + rs;
    T->mx = max(lmx, ls + T->val);
    T->mx = max(T->mx, ls + T->val + rmx);
}

//左旋
void RotateWithRightChild(pnode & T)
{
    pnode X = T->right;
    T->right = X->left;
    X->left = T;
    T = X;
    Update(T->left);
}

//右旋
void RotateWithLeftChild(pnode & T)
{
    pnode X = T->left;
    T->left = X->right;
    X->right = T;
    T = X;
    Update(T->right);
}

void Insert(pnode & p, int key, int val)
{
    if(p == NULL)
    {
        p = new node;
        p->key = key;
        p->val = val;
        p->left = NULL;
        p->right = NULL;
    }
    else if(key == p->key)
    {
        p->val += val;
    }
    else if(key < p->key)
    {
        Insert(p->left, key, val);
        if(p->left->mx > p->mx)
            RotateWithLeftChild(p);
    }
    else
    {
        Insert(p->right, key, val);
        if(p->right->mx > p->mx)
            RotateWithRightChild(p);
    }

    Update(p);
}

int main()
{
    int S, W, N;
    scanf("%d %d %d", &S, &W, &N);

    for(int i = 1; i <= N; i++)
    {
        scanf("%d %d", &mine[i].x, &mine[i].y);
        mine[i].x += OFFSET;
        mine[i].y += OFFSET;
    }

    sort(mine + 1, mine + N + 1);

    int l = 1, r, pre = 1, ans = 0;

    while(l <= N)
    {
        r = l;

        while(r <= N && mine[r].x == mine[l].x)
        { 
            Insert(root, mine[r].y, 1);
            Insert(root, mine[r].y + W + 1, -1);
            r ++;
        }//此时r指向下一个x坐标的第一个点

        //移除区间扫过的点，只保留S宽度的点
        while(mine[pre].x < mine[l].x - S)
        {
            Insert(root, mine[pre].y, -1);
            Insert(root, mine[pre].y + W + 1, 1);
            pre ++;
        }

        l = r;

        ans = max(ans, root->mx);
    }

    printf("%d\n", ans);

    return 0;
}
