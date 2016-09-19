#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int arr[1005];
bool vis[1005];

int main()
{
    int turn, a, n, l;
    cin >> turn;

    while(turn --)
    {
        cin >> n >> l;

        memset(arr, 0, sizeof(arr));
        memset(vis, 0, sizeof(vis));

        for(int i = 1; i <= l; i++)
        {
            cin >> arr[i];
        }

        bool flag = false, flag2 = true;
        int count;
        for(int i = 1; i <= n; i++)
        {
            flag2 = true;
            memset(vis, 0, sizeof(vis));

            for(int j = 1; j < i; j++)
            {
                if(vis[arr[j]])
                {
                    flag2 = false;
                    break;
                }
                else
                {
                    vis[arr[j]] = true;
                }
            }

            if(flag2)
            {
                memset(vis, 0, sizeof(vis));
                count = 0;
                for(int j = i; j <= l && flag2; j++)
                {
                    if(vis[arr[j]])
                    {
                        flag2 = false;
                        break;
                    }
                    else
                    {
                        vis[arr[j]] = true;
                    }

                    count ++;

                    if(count == n)
                    {
                        count = 0;
                        memset(vis, 0, sizeof(vis));
                    }
                }
            }

            if(flag2)
            {
                flag = true;
                break;
            }
        }

        if(flag)
            cout << "CAN'T DECIDE" << endl;
        else
            cout << "B" << endl;
    }

    return 0;
}