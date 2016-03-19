#include <iostream>
#include <queue>
using namespace std;

const int maxn = 100;
typedef struct node
{
	int r;
	int c;
} Node;

queue<Node *> que;
int maxd = 0, maxc = 0, maxr = 0;
int labyrinth[maxn][maxn] = {0};
int dis[maxn][maxn] = {0};
int m, n;

int trypush(int r, int c)
{
	if(r < 0 || r >= m || c < 0 || c >= n || dis[r][c] != -1)
	{
		return 0;
	}
	else
	{
		Node * t = new Node;
		t->r = r;
		t->c = c;
		que.push(t);

		return 1;
	}
}

void bfs(int cur, int next, int layer)
{
	while(que.size() != 0)
	{
		Node * temp = que.front();
		que.pop();
		cur -= 1;

		int r = temp->r;
		int c = temp->c;
		free(temp);

		if(layer > maxd)
		{
			maxd = layer;
			maxc = c;
			maxr = r;
		}

		if(dis[r][c] == -1) dis[r][c] = layer;

		next += trypush(r + 1, c);
		next += trypush(r, c + 1);
		next += trypush(r - 1, c);
		next += trypush(r, c - 1);

		if(cur == 0)
		{
			cur = next;
			next = 0;
			layer += 1;
		}
	}
}

int main()
{
	scanf("%d %d", &m, &n);

	for(int i = 0; i < m; i++)
	{
		for(int j = 0; j < n; j++)
		{
			scanf("%d", &labyrinth[i][j]);
			if(labyrinth[i][j] == 0) dis[i][j] = 999;
			else dis[i][j] = -1;
		}
	}

	Node * st = new Node;
	st->r = 0;
	st->c = 0;

	que.push(st);

	bfs(1, 0, 0);

	for(int i = 0; i < m; i++)
	{
		for(int j = 0; j < n; j++)
		{
			printf("%4d ",dis[i][j]);
		}
		printf("\n");
	}
	printf("MAX:(%d,%d) = %d\n",maxr, maxc, maxd);

	return 0;
}