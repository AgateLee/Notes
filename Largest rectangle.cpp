#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

typedef struct node{
    int key, val;
    int f, l, r;

    bool operator < (node t) const
    {
        return key < t.key;
    }
} node;

vector<node> T;
vector<int> stack;
int top;

int create(int n)
{
    top = 1;
    stack.push_back(1);
    for(int i = 2; i <= n; i++)
    {
        while(top > 0 && T[i].val < T[stack[top]].val)
            top --;
        if(top > 0) // 右链中的节点
        {
            T[i].f = stack[top];
            T[i].l = T[stack[top]].r;
            T[T[stack[top]].r].f = i;
            T[stack[top]].r = i;

            if(top == stack.size() - 1)
            {
                top ++;
                stack.push_back(i);
            }
            else
            {
                stack[++top] = i;
            }
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

int solve(int r, int & ans)
{
    int temp = 1;

    if(T[r].l)
        temp += solve(T[r].l, ans);
    if(T[r].r)
        temp += solve(T[r].r, ans);

    int ans2 = temp * T[r].val;

    if(ans2 > ans)
        ans = ans2;

    // cout << T[r].key << " " << temp << endl;
    return temp;
}

int main()
{
    int n;
    scanf("%d", &n);
    T.clear();
    stack.clear();

    node flag = {0, 0, 0, 0, 0};
    T.push_back(flag);
    stack.push_back(0);

    for(int i = 1; i <= n; i++)
    {
        node temp = {0, i, 0, 0, 0};
        scanf("%d", &temp.val);
        T.push_back(temp);
    }
    
    sort(T.begin(), T.end());
    int root = create(n);
    
    int ans = 0;
    solve(root, ans);
    cout << ans << endl;

    return 0;
}