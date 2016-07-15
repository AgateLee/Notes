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

point mine[MAXN];

typedef struct node{
    int key, val, sum, mx;
    struct node * left, * right, * parent;

    node(const int n, const int m):key(n), val(m), sum(m), mx(m),
        left(NULL), right(NULL), parent(NULL){};
    ~node()
    {
        if(left)
            delete left;
        if(right)
            delete right;
    };
} node, * pnode;

class SplayTree{
private:
    void Update(pnode & T);
    void zig(pnode T);
    void zag(pnode T);
    void splay(pnode T, pnode ANC);
    void splay(pnode & T);
    void insert(pnode & T, int key, int val);

public:
    pnode root;

    SplayTree()
    {
        root = NULL;
    }

    ~SplayTree()
    {
        if(root)
            delete root;
    }

    void Insert(int key, int val);
};

void SplayTree::Update(pnode & T)
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

//右旋
void SplayTree::zig(pnode x)
{
    pnode p = x->parent;
    x->parent = p->parent;

    if(p->parent != NULL)
    {
        if(p->parent->left == p)
            p->parent->left = x;
        else
            p->parent->right = x;
    }
    else root = x;

    p->left = x->right;
    if(x->right != NULL)
        x->right->parent = p;
    x->right = p;
    p->parent = x;

    Update(p);
}

//左旋
void SplayTree::zag(pnode x)
{
    pnode p = x->parent;
    x->parent = p->parent;

    if(p->parent != NULL)
    {
        if(p->parent->left == p)
            p->parent->left = x;
        else
            p->parent->right = x;
    }
    else root = x;

    p->right = x->left;
    if(x->left != NULL)
        x->left->parent = p;
    x->left = p;
    p->parent = x;

    Update(p);
}

//T转为ANC的孩子, 需要保证ANC是T的祖先
void SplayTree::splay(pnode T, pnode ANC)
{
    pnode p = NULL, g = NULL;

    while(T != NULL && T->parent != ANC)
    {
        p = T->parent;
        if(p->parent == ANC)
        {
            p->left == T ? zig(T) : zag(T);
        }
        else
        {
            g = p->parent;
            if(g->left == p)
            {
                p->left == T ? zig(p) : zag(T), zig(T);
            }
            else
            {
                p->left == T ? zig(T) : zag(p), zag(T);
            }
        }
    }
}

void SplayTree::insert(pnode & T, int key, int val)
{
    if(T == NULL)
    {
        T = new node(key, val);
    }
    else if(T->key == key)
    {
        T->val += val;
        splay(T, NULL);
    }
    else if(T->key > key)
    {
        if(T->left == NULL)
        {
            T->left = new node(key, val);
            T->left->parent = T;
            splay(T->left, NULL);
        }
        else insert(T->left, key, val);
    }
    else
    {
        if(T->right == NULL)
        {
            T->right = new node(key, val);
            T->right->parent = T;
            splay(T->right, NULL);
        }
        else insert(T->right, key, val);
    }

    Update(T);
}

void SplayTree::Insert(int key, int val)
{
    insert(root, key, val);
}

int main()
{
    int S, W, N;
    SplayTree ST;

    freopen("kop.in","r",stdin);
    freopen("kop.out","w",stdout);

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
            ST.Insert(mine[r].y, 1);
            ST.Insert(mine[r].y + W + 1, -1);
            r ++;
        }//此时r指向下一个x坐标的第一个点

        //移除区间扫过的点，只保留S宽度的点
        while(mine[pre].x < mine[l].x - S)
        {
            ST.Insert(mine[pre].y, -1);
            ST.Insert(mine[pre].y + W + 1, 1);
            pre ++;
        }

        l = r;

        ans = max(ans, ST.root->mx);
    }

    printf("%d\n", ans);

    return 0;
}
