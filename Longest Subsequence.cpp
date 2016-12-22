#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 26;

typedef struct node{
    int pos;
    bool exist;
    struct node * next[MAXN];
} TrieNode, * pTrieNode;

TrieNode Memory[1000000]; //先分配内存, 动态分配太耗时
int allocp = 0;
int MAXL = 0;

pTrieNode CreateTrie()
{
    pTrieNode temp = &Memory[allocp ++];
    temp->pos = 0;
    temp->exist = false;
    memset(temp->next, 0, sizeof(temp->next));

    return temp;
}

void InsertTrie(pTrieNode & root, string str)
{
    pTrieNode temp = root;

    int i = 0, k;

    while(str[i])
    {
        k = str[i] - 'a';
        if(temp->next[k] == NULL)
            temp->next[k] = CreateTrie();

        temp = temp->next[k];
        i++;
    }

    temp->exist = true;
}

void search(pTrieNode & root, string m, int st, int cur)
{
	for(int i = 0; i < MAXN; i++)
	{
		pTrieNode & p = root->next[i];
		if(p != NULL)
		{
			p->pos = m.find_first_of('a' + i, st);

			// cout << "Find " << (char)('a' + i) << " at " << p->pos << " ,cur " << cur << endl;
			if(p->pos != -1)
			{
				cur ++;

				if(p->exist)
					MAXL = cur > MAXL ? cur : MAXL;
				search(p, m, p->pos + 1, cur);

				cur --;
			}
		}
	}
}

int main()
{
    int n;
    string s, match;
    pTrieNode root = CreateTrie();

    scanf("%d", &n);
    getchar();
    while(n --)
    {
        getline(cin, s);
        InsertTrie(root, s);
    }
    getline(cin, match);
    
    search(root, match, 0, 0);

    printf("%d\n", MAXL);

    return 0;
}