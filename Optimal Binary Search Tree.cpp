#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 200;
const int INF = 1 << 30;
int N;
double p[MAXN], q[MAXN];

int root[MAXN][MAXN];
double w[MAXN][MAXN], e[MAXN][MAXN];

void optBST()
{
    //初始化伪关键字节点
    for(int i = 0; i <= N; i++)
    {
        w[i + 1][i] = q[i];
        e[i + 1][i] = q[i];
    }

    int j;
    double temp;

    for(int len = 1; len <= N; len++)
    {
        for(int i = 1; i <= N - len + 1; i++)
        {
            j = i + len - 1;
            e[i][j] = INF;
            w[i][j] = w[i][j - 1] + p[j] + q[j];
            for(int k = i; k <= j; k++)
            {
                temp = e[i][k - 1] + e[k + 1][j] + w[i][j];
                if(temp < e[i][j])
                {
                    e[i][j] = temp;
                    root[i][j] = k;
                }
            }
        }
    }
}

void printBST(int i, int j, int r)
{
    int rc = root[i][j];

    if(root[i][j] == root[1][N])
    {
        cout << "k " << rc << " is root" << endl;
        printBST(i, rc - 1, rc);
        printBST(rc + 1, j, rc);

        return;
    }

    if(j < i - 1)
        return;
    else if(j == i - 1)
    {
        if(j < r) 
            cout << "d " << j << " is left child of " << r << endl;
        else
            cout << "d " << j << " is right child of " << r << endl;

        return;
    }
    else
    {
        if(rc < r) 
            cout << "k " << rc << " is left child of " << r << endl;
        else
            cout << "k " << rc << " is right child of " << r << endl;
    }

    printBST(i, rc - 1, rc);
    printBST(rc + 1, j, rc);
}

int main()
{
    scanf("%d",&N);

    for(int i = 1; i <= N; i++)
    {
        scanf("%lf", &p[i]);
    }

    for(int i = 0; i <= N; i++)
    {
        scanf("%lf", &q[i]);
    }

    optBST();
    cout << "ANS = " << e[1][N] << endl;
    printBST(1, N, -1);

    return 0;
}