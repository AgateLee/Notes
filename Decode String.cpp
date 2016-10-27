#include <cstdio>
#include <iostream>
#include <cstring>
#include <sstream>
#include <stack>
#include <cctype>
using namespace std;

const int MAXN = 3;

string decode(string s)
{
	stack<string> st;
	string cut = "", cur = "";
	s += '$';
	int len = s.length();

	bool d = false, al = false;
	string c;
	for(int i = 0; i < len; i++)
	{
		if(s[i] != ']' && s[i] != '$') // in stack
		{
			if(s[i] == '[')
			{
				if(cut != "")
					st.push(cut);
				cut = "";
				st.push("[");
				d = al = false;
				continue;
			}
			else if(isdigit(s[i]) && !d)
			{
				if(cut != "")
					st.push(cut);
				cut = "";
				d = true;
				al = false;
			}
			else if(!isdigit(s[i]) && !al)
			{
				if(cut != "")
					st.push(cut);
				cut = "";
				al = true;
				d = false;
			}

			cut += s[i];
		}
		else
		{
			if(cut != "")
			{
				st.push(cut);
				cut = "";
			}
			d = al = false;
			while(!st.empty())
			{
				c = st.top();
				st.pop();
				if(c[0] == '[')
					continue;

				if(isdigit(c[0]))
				{
					int num = 0;
					string temp = "";
					stringstream ss;
					ss << c;
					ss >> num;

					while(num --)
						temp = temp + cur;
					cur = temp;
					break;
				}
				else
				{
					cur = c + cur;
				}
			}

			if(s[i] == '$')
				return cur;
			else
			{
				st.push(cur);
				cur = "";
			}
		}
	}

	return "";
}

int main()
{
	string s[] = {"sd2[f2[e]g]i", "3[a]2[bc]", "3[a2[c]]"};
	
	for(int i = 0; i < MAXN; i++)
	{
		cout << decode(s[i]) << endl;
	}

	return 0;
}
