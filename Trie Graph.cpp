#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

const int MAXN = 26;
string s, target;

typedef struct TrieNode{
    bool exist;
    TrieNode * fail, * next[MAXN];

    TrieNode()
    {
        exist = false;
        fail = NULL;
        memset(next, 0, sizeof(next));
    }
} TrieNode, * pTrieNode;

void TrieInsert(pTrieNode & root, string s)
{
    int id, len = s.length();
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

    p->exist = true;
}

void BuildAC(pTrieNode root)
{
    int rear = 1, front = 0, i;
    pTrieNode p, tmp;
    queue<pTrieNode> que;
    que.push(root);

    // 逐层计算每一层节点的fail指针，每个节点计算完毕，保证其所有后继都已计算
    while(! que.empty())
    {
        p = que.front();
        que.pop();

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
                            if(tmp->next[i]->exist == true)
                                p->next[i]->exist = true;
                            break;
                        }
                        tmp = tmp->fail;
                    }

                    if(tmp == NULL)
                        p->next[i]->fail = root;
                }

                que.push(p->next[i]);
            }
        }
    }
}

bool QueryAC(pTrieNode root, string s)
{
    pTrieNode p = root, tmp = NULL;
    int id, len = s.length();

    for(int i = 0; i < len; i++)
    {
        id = s[i] - 'a';

        while(true)
        {
            if(p->next[id] != NULL)
            {
                p = p->next[id];

                if(p->exist == true)
                    return true;
                break;
            }
            else
                p = p->fail;

            if(p == root || p == NULL)
            {
                p = root;
                break;
            }
        }
    }

    return false;
}

int main()
{
    int N;
    // freopen("input.txt", "r", stdin);
    
    cin >> N;
    pTrieNode root = new TrieNode;

    for(int i = 1; i <= N; i++)
    {
        cin >> s;
        TrieInsert(root, s);
    }
    BuildAC(root);

    cin >> target;
    printf("%s\n", QueryAC(root, target) ? "YES" : "NO");

    return 0;
}