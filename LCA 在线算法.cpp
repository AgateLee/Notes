#include <iostream>
#include <cstring>
#include <vector>
#include <unordered_map>
using namespace std;

const int MAXN = 100010;

struct Node{
    int pre, h;
} tree[MAXN];

unordered_map<string, int> ord;
unordered_map<int, int> leave;
vector<int> suc[MAXN];
string names[MAXN];
int mylist[MAXN<<1], sz = 0;

int myhash(string s)
{
    if(ord.find(s) == ord.end())
    {
        names[sz] = s;
        ord[s] = sz ++;
    }

    return ord[s];
}

void build(int pos, int h)
{
    tree[pos].h = h;
    mylist[sz ++] = pos;

    for(int i = 0; i < suc[pos].size(); i ++)
    {
        build(suc[pos][i], h + 1);
        mylist[sz ++] = pos;
    }
    
    leave[pos] = sz - 1;
}

int main()
{
    int n, a, b;
    string s1, s2;

    cin >> n;
    while(n --)
    {
        cin >> s1 >> s2;
        a = myhash(s1);
        b = myhash(s2);

        tree[b].pre = a;
        suc[a].push_back(b);
    }
    sz = 0;
    build(0, 0);
    // cout << sz << endl;
    // cout << ord.size() << endl;
    // for(int i = 0; i < sz; i++)
    // {
    //     cout << " " << i << "_" << names[mylist[i]] << leave[mylist[i]];
    // }
    // cout << endl;
    cin >> n;
    while(n --)
    {
        cin >> s1 >> s2;
        a = ord[s1];
        b = ord[s2];

        a = leave[a];
        b = leave[b];

        if(a > b)
        {
            a ^= b;
            b ^= a;
            a ^= b;
        }

        int mh = MAXN, ans = 0;

        for(int i = a; i <= b; i ++)
        {
            if(tree[mylist[i]].h < mh)
            {
                mh = tree[mylist[i]].h;
                ans = mylist[i];
            }
        }

        cout << names[ans] << endl;
    }

    return 0;
}