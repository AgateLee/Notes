#include <iostream>
#include <queue>
using namespace std;

typedef class Node
{
public:
	int r;
	int c;
	int dir;

	Node()
	{
		r = 0;
		c = 0;
		dir = 0;
	};

	Node(int r0, int c0, int dir0)
	{
		r = r0;
		c = c0;
		dir = dir0;
	};

	~Node()
	{

	};
}Node;

class Node st, ed;	

const int maxn = 10;
//r,c处面朝dir时是否允许turn方向
int has_edge[maxn][maxn][4][3] = {0};
int d[maxn][maxn][4] = {0};
Node p[maxn][maxn][4];

//定义方向转换函数
const char * dirs = "NESW"; //朝向顺时针
const char * turns = "FLR";

int dir_id(char c)
{
	return strchr(dirs, c) - dirs;
}

int turn_id(char c)
{
	return strchr(turns, c) - turns;
}

//定义行走函数
//NESW，r改南北，c改东西
const int dr[] = {-1, 0, 1, 0}; //北  南
const int dc[] = {0, 1, 0, -1}; //  东  西

//位置u处的尝试
Node walk(const Node &u, int turn)
{
	int dir = u.dir; //面朝dir

	//0直行
	if(turn == 1)
	{
		dir = (dir + 3)%4; //1左转 顺时针3
		printf("turn Left\n");
	} 
	else if(turn == 2) 
	{
		dir = (dir + 1)%4; //2右转 顺时针1
		printf("turn Right\n");
	}
	else printf("go Straight\n");
	//  L    R
	//N W 3  E 1 
	//E N 3  S 1
	//S E 3  W 1
	//W S 3  N 1

	//0朝北左转，顺3，3西，dc[3] = -1 
	//0朝北右转，顺1，1东，dc[1] = 1
	//1朝东左转，顺3，0北，dr[0] = -1
	//1朝东右转，顺1，2南，dr[2] = 1
	//2朝南左转，顺3，1东，dc[1] = 1
	//2朝南右转，顺1，3西，dc[3] = -1
	//3朝西左转，顺3，2南，dr[2] = 1
	//3朝西右转，顺1，0北，dr[0] = -1

	return Node(u.r + dr[dir], u.c + dc[dir], dir);
}

void readMap()
{
	int n, r, c;
	scanf("%d", &n);

	for(int i = 0; i < n; i ++)
	{
		scanf("%d %d", &r, &c);
		char ch = 'A', ch2 = 'A';
		while(ch2 != '\n' && (ch = getchar()) != '\n')
		{
			if(ch != ' ')
			{
				while((ch2 = getchar()) != ' ' && ch2 != '\n')
				{
					has_edge[r][c][dir_id(ch)][turn_id(ch2)] = 1;
					printf("(%d,%d),towards %c, turn %c\n",r, c, ch, ch2);
				}
			}
		}
	}
}

void print_ans(Node u)
{
	vector<Node> nodes;

	for(;;)
	{
		nodes.push_back(u);
		if(d[u.r][u.c][u.dir] == 0)
			break;
		u = p[u.r][u.c][u.dir];
	}
	nodes.push_back(st);

	int cnt = 0;

	for(int i = nodes.size() - 1; i >= 0; i--)
	{
		if(cnt % 10 == 0) printf(" ");
		printf(" (%d,%d)",nodes[i].r, nodes[i].c);
		if(++cnt % 10 == 0) printf("\n");
	}

	if(nodes.size() % 10 != 0) printf("\n");
}

void solve()
{
	queue<Node> q;
	memset(d, -1, sizeof(d));

	Node t = walk(st, 0);
	d[t.r][t.c][t.dir] = 0;
	q.push(t);

	while(!q.empty())
	{
		Node u = q.front();
		printf("(%d,%d) towards %d\n",u.r, u.c, u.dir);
		q.pop();

		if(u.r == ed.r && u.c == ed.c)
		{
			print_ans(u);
			return;
		}

		for(int i = 0; i < 3; i ++)
		{
			if(has_edge[u.r][u.c][u.dir][i])
			{
				Node v = walk(u, i);

				if(d[v.r][v.c][v.dir] < 0)
				{
					d[v.r][v.c][v.dir] = d[u.r][u.c][u.dir] + 1;

					p[v.r][v.c][v.dir] = u;
					q.push(v);
				}
			}
		}
	}

	printf("No solution!\n");
}

int main()
{
	char dir;
	scanf("%d %d %c",&st.r, &st.c, &dir);
	st.dir = dir_id(dir);
	scanf("%d %d",&ed.r, &ed.c);
	printf("st: (%d,%d), dir:%d\n", st.r, st.c, st.dir);
	printf("ed: (%d,%d)\n", ed.r, ed.c);
	readMap();

	solve();

	return 0;
}