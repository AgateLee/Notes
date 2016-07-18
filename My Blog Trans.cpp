#include <cstdio>
#include <fstream>
using namespace std;

int main()
{
    ifstream f("1.wp");
    ofstream of("2.wp");

    char c;
    bool flag = true, flag1 = true, flag2 = true, flag3 = true;
    while(f.get(c))
    {
        if(c == '$')
        {
            if(flag)
            {
                of << "[latex]";
            }
            else
            {
                of << "[/latex]";
            }
            flag = !flag;
        }
        else if(c == '\n')
        {
            if(!flag1)
            {
                flag1 = !flag1;
                of << "</span>";
            }
            of << c;
        }
        else if(c == '#')
        {
            char c2,c3;
            f.get(c2);
            f.get(c3);

            if(c2 == c && c3 != c)
            {
                of << "<span class=\"ly-2\">";
                of << c3;
                flag1 = !flag1;
            }
            else
            {
                of << c << c2 << c3;
            }
        }
        else if(c == '`')
        {
            char c2, c3, c4;
            f.get(c2);
            
            if(c2 == c)
            {
                f.get(c3);
                if(flag2)
                {
                    f.get(c4);
                    f.get(c4);
                    f.get(c4);
                    f.get(c4);
                    of << "<pre><code class=\"language-cpp\">";
                }
                else
                {
                    of << "</code></pre>";
                }
                flag2 = !flag2;
            }
            else
            {
                of << c << c2;
                flag3 = !flag3;
            }
            
        }
        else if(c == '<')
        {
            if(flag3)
                of << "&lt;";
            else
                of << c;
        }
        else if(c == '>')
        {
            if(flag3)
                of << "&gt;";
            else
                of << c;
        }
        else
        {
            of << c;
        } 
    }

    return 0;
}