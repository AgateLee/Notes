#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 1000;

typedef struct node{
    int id;
    int key, val;
    int f, l, r;

    bool operator < (node t) const
    {
        return key < t.key;
    }
} node;

node T[MAXN];
int stack[MAXN], top;

int create(int n)
{
    top = 1;
    stack[top] = 1;
    for(int i = 2; i <= n; i++)
    {
        while(top > 0 && T[i].val > T[stack[top]].val)
            top --;
        if(top > 0) // 右链中的节点
        {
            T[i].f = stack[top];
            T[i].l = T[stack[top]].r;
            T[T[stack[top]].r].f = i;
            T[stack[top]].r = i;
            stack[++top] = i;
        }
        else // 根节点
        {
            T[stack[1]].f = i;
            T[i].l = stack[1];
            stack[++top] = i;
        }
    }

    return stack[1];
}

void show(int i)
{
    cout << "id: " << T[i].id << " key: " << T[i].key
         << " val: " << T[i].val << " fa: " << T[T[i].f].key
         << " l: " << T[T[i].l].key << " r: " << T[T[i].r].key << endl;

    if(T[i].l)
    {
        show(T[i].l);
    }

    if(T[i].r)
    {
        show(T[i].r);
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    memset(T, 0, sizeof(T));

    for(int i = 1; i <= n; i++)
    {
        scanf("%d %d", &T[i].key, &T[i].val);
        T[i].id = i;
    }
    
    sort(T + 1, T + n + 1);
    int root = create(n);
    
    show(root);

    return 0;
}