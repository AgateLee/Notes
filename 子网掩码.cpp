#include <iostream>
#include <string.h>

using namespace std;

typedef struct node
{
	char sign;
	int no;

	struct node * l, * r;
}Node, * pNode;

string change(int n)
{
	string r = "";

	for(int i = 7; i >= 0; i--)
	{
		if((n >> i)&0x01) r += '1';
		else r += '0';
	}

	return r;
}

string getstr(int a, int b, int c, int d)
{
	return change(a) + change(b) + change(c) + change(d);
}

pNode createNode()
{
	pNode p = new Node;

	p->no = -1;
	p->sign = 'a';
	p->l = NULL;
	p->r = NULL;

	return  p;
}

void insertNode(pNode fa, string add, int cur, int mask, int no, char sign)
{
	if(cur == mask)
		return;

	pNode p = NULL;

	if(add[cur] == '0')
	{
		if(fa->l == NULL) fa->l = createNode();
		p = fa->l;
	}
	else
	{
		if(fa->r == NULL) fa->r = createNode();
		p = fa->r;
	}
	
	if(cur == mask - 1 && p->no == -1)
	{
		p->no = no;
		p->sign = sign;
	}

	insertNode(p, add, cur + 1, mask, no, sign);
}

char findNode(pNode root, string add)
{
	int i;
	pNode p = root;
	int min = root->no == -1 ? 999999 : root->no;
	char sign = root->no == -1 ? 'a' : root->sign;

	for(i = 0; i < 32; i++)
	{
		if(add[i] == '0')
			p = p->l;
		else 
			p = p->r;

		if(p == NULL)
			break;

		if(p->no != -1 && min > p->no)
		{
			min = p->no;
			sign = p->sign;
		}
	}
	// cout << i << endl;
	return sign;
}

int main()
{
	int m, n, a, b, c, d, mask;
	char s[256], sign, *p;
	string add;
	pNode root = createNode();

	cin.getline(s, 256);
	sscanf(s, "%d %d", &n, &m);

	for(int i = 0; i < n; i++)
	{
		cin.getline(s, 256);
		sign = s[0];
		p = strchr(s, ' ');

		sscanf(p, "%d.%d.%d.%d", &a, &b, &c, &d);
		p = strchr(s, '/');

		if(p != NULL) sscanf(p + 1, "%d", &mask);
		else mask = 32;

		add = getstr(a, b, c, d);

		if(mask)
		{
			// cout << "insert " << add << " " << mask <<  " " << sign << endl;
			insertNode(root, add, 0, mask, i, sign);
		}
		else if(root->no == -1)
		{
			// cout << "default " << sign << endl;
			root->no = i;
			root->sign = sign;
		}
	}

	for(int i = 0; i < m; i++)
	{
		cin.getline(s, 256);
		sscanf(s, "%d.%d.%d.%d", &a, &b, &c, &d);
		add = getstr(a, b, c, d);
		// cout << "find   " << add << endl;
		if(findNode(root, add) == 'a')
			cout << "YES" << endl;
		else 
			cout << "NO" << endl;
	}

	return 0;
}