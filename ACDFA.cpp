#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 26;
const int MAXQ = 500010;
char s[64], target[1000010];

typedef struct TrieNode{
    int cnt;
    TrieNode * fail, * next[MAXN];

    TrieNode()
    {
        cnt = 0;
        fail = NULL;
        memset(next, 0, sizeof(next));
    }
} TrieNode, * pTrieNode;

pTrieNode que[MAXQ];

void TrieInsert(pTrieNode & root, char * s)
{
    int id, len = strlen(s);
    pTrieNode p = root;

    for(int i = 0; i < len; i++)
    {
        id = s[i] - 'a';
        if(p->next[id] == NULL)
        {
            p->next[id] = new TrieNode;
        }
        p = p->next[id];
    }

    p->cnt ++;
}

void BuildAC(pTrieNode root)
{
    int rear = 1, front = 0, i;
    pTrieNode p, tmp;
    que[0] = root;

    // 逐层计算每一层节点的fail指针，每个节点计算完毕，保证其所有后继都已计算
    while(rear != front)
    {
        p = que[front ++];

        for(i = 0; i < MAXN; i++)
        {
            if(p->next[i] != NULL)
            {
                if(p == root)
                    p->next[i]->fail = root;
                else
                {
                    tmp = p->fail;
                    while(tmp != NULL)
                    {
                        if(tmp->next[i] != NULL)
                        {
                            p->next[i]->fail = tmp->next[i];
                            break;
                        }
                        tmp = tmp->fail;
                    }

                    if(tmp == NULL)
                        p->next[i]->fail = root;
                }

                que[rear ++] = p->next[i];
            }
        }
    }
}

int QueryAC(pTrieNode root, char * s)
{
    pTrieNode p = root, tmp = NULL;
    int sum = 0, id, len = strlen(s);

    for(int i = 0; i < len; i++)
    {
        id = s[i] - 'a';

        //跳转失败指针
        while(p != root && p->next[id] == NULL)
            p = p->fail;
        p = p->next[id];

        if(p == NULL)
            p = root;

        tmp = p;

        while(tmp != root && tmp->cnt != -1)
        {
            sum += tmp->cnt;
            tmp->cnt = -1;
            tmp = tmp->fail;
        }
    }

    return sum;
}

int main()
{
    int T, N;
    // freopen("input.txt", "r", stdin);
    scanf("%d", &T);

    while(T --)
    {
        scanf("%d", &N);
        pTrieNode root = new TrieNode;

        for(int i = 1; i <= N; i++)
        {
            scanf("%s", s);
            TrieInsert(root, s);
        }
        BuildAC(root);

        scanf("%s", target);
        printf("%d\n", QueryAC(root, target));
    }

    return 0;
}