#include <iostream>
#include <queue>
using namespace std;

const int maxn = 100;
typedef struct node
{
	int r;
	int c;
	int layer;
} Node;

queue<Node *> que;
int maxd = 0, maxc = 0, maxr = 0;
int labyrinth[maxn][maxn] = {0};
int dis[maxn][maxn] = {0};
int m, n;	

void trypush(int r, int c, int layer)
{
	if(r < 0 || r >= m || c < 0 || c >= n || dis[r][c] != -1)
	{
		return;
	}
	else
	{
		Node * t = new Node;
		t->r = r;
		t->c = c;
		t->layer = layer;
		que.push(t);
	}
}

void bfs()
{
	if(que.size() == 0)
		return;

	Node * temp = que.front();
	que.pop();
	int r = temp->r;
	int c = temp->c;
	int layer = temp->layer;
	free(temp);

	if(layer > maxd)
	{
		maxd = layer;
		maxc = c;
		maxr = r;
	}

	if(dis[r][c] == -1) dis[r][c] = layer;
	layer += 1;

	trypush(r + 1, c, layer);
	trypush(r, c + 1, layer);
	trypush(r - 1, c, layer);
	trypush(r, c - 1, layer);

	bfs();
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
	st->layer = 0;

	que.push(st);
	bfs();

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