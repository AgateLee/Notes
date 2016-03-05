#include <cstdio>

const int maxn = 100 + 10;
int Pr[maxn], In[maxn], Po[maxn];

int find(int list[maxn], int st, int end, int n)
{
    for(int i = st; i <= end; i ++)
    {
        if(list[i] == n)
            return i;
    }
    
    return -1;
}

void  loop(int pr_st, int pr_end, int In_st, int In_end)
{
    if(pr_st == pr_end)
    {
        printf("%d ",Pr[pr_st]);
        return;
    }   
    
    int root = Pr[pr_st];
    int root_pos = find(In, In_st, In_end, root);
    int count_l = root_pos - In_st;
    int count_r = In_end - root_pos;
    
    if(count_l >0)
        loop(pr_st + 1, pr_st + count_l, In_st, root_pos - 1);
        
    if(count_r > 0)
        loop(pr_st + count_l + 1, pr_end, root_pos + 1, In_end);
        
    printf("%d ", root);
}

int main()
{
    int n;
    while(scanf("%d", &n) == 1 && n)
    {
        for(int i = 1; i <= n; i ++)
            scanf("%d", &Pr[i]);
            
        for(int i = 1; i <= n; i ++)
            scanf("%d", &In[i]);
            
        loop(1, n, 1, n);
    }

    return 0;
}
