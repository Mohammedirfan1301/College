#include<iostream>
#include<cstdio>
#include<string>
#include<algorithm>
using namespace std;
int main()
{
    int T;
    string str;
    scanf("%d%*c",&T);
    while(T--)
    {
        getline(cin, str);

        int i = 0;
        while(!str.empty())
        {
            if(str[i] == ')')
            {
                i--;
                if(str[i] == '(')
                {
                    str.erase(i,2);
                    continue;
                }
                else
                {
                    printf("No\n");
                    break;
                }
            }
            else if(str[i] == ']')
            {
                i--;
                if(str[i] == '[')
                {
                    str.erase(i,2);
                    continue;
                }
                else
                {
                    printf("No\n");
                    break;
                }
            }
            else   i++;
        }
        if(str.empty())    printf("Yes\n");
        str.clear();
    }
    return 0;
}
