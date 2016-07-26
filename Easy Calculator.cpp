#include <iostream>
#include <stack>
#include <cstring>
#include <cctype>
using namespace std;

stack<int> num;
stack<char> op;

void cal(char o)
{
    int second = num.top();
    num.pop();
    int first = num.top();
    num.pop();
    // cout << first << o << second << endl;
    switch(o)
    {
        case '+':
            num.push(first + second);
        break;
        case '-':
            num.push(first - second);
        break;
        case '*':
            num.push(first * second);
        break;
        case '/':
            num.push(first / second);
        break;
    }
}

int main()
{
    string s;
    int cur = 0;
    getline(cin, s);

    for(int i = 0; i < s.length(); i++)
    {
        if(isdigit(s[i]))
        {
            cur = s[i++] - '0';
            while(isdigit(s[i]))
            {
                cur *= 10;
                cur += s[i] - '0';
                i++;
            }
            num.push(cur);
            i --;
        }
        else
        {
            switch(s[i])
            {
                case '(':
                    op.push('(');
                break;
                case '+':
                case '-':
                    while(!op.empty() && op.top() != '(')
                    {
                        cal(op.top());
                        op.pop();
                    }
                    op.push(s[i]);
                break;
                case ')':
                    while(!op.empty() && op.top() != '(')
                    {
                        cal(op.top());
                        op.pop();
                    }
                    if(!op.empty() && op.top() == '(')
                        op.pop();
                    break;
                case '*':
                case '/':
                    while(!op.empty() && (op.top() == '*' || op.top() == '/'))
                    {
                        cal(op.top());
                        op.pop();
                    }
                    op.push(s[i]);
                break;
            }
        }
    }

    while(!op.empty())
    {
        cal(op.top());
        op.pop();
    }

    printf("%d\n", num.top());

    return 0;
}