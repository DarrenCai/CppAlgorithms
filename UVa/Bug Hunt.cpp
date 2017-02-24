/**
 * UVa1596
 * 找bug
 */

#include <iostream>
#include <string>
#include <stack>
#include <map>

int main()
{
    using namespace std;
    string line;
    while(cin>>line && line[0]!='.')
    {
        int num = 0;
        bool find = false;
        int len[52] = { 0 };
        map<int, int> ass[52];
        while(++num && line[0] != '.')
        {
            if(!find)
            {
                char c;
                int n, i;
                stack<char> stak;
                const int l = line.length();
                for(i=0; !find && i<l && line[i]!='='; ++i)
                {
                    if(line[i]<'A')
                    {
                        n = line[i] - '0';
                        while(line[++i] < 'A')
                        {
                            n = 10*n + line[i] - '0';
                        }
                        while(!find && !stak.empty())
                        {
                            c = stak.top();
                            c -= c>'Z' ? 'a'-26 : 'A';
                            stak.pop();
                            if(!stak.empty())
                            {
                                ++ i;
                                if(len[c])
                                {
                                    if(n>=len[c] || (n<len[c] && !ass[c].count(n)))
                                    {
                                        cout << num << endl;
                                        find = true;
                                    }
                                    if(!find)
                                    {
                                        n = ass[c][n];
                                    }
                                }
                            }
                        }
                    }
                    else
                    {
                        stak.push(line[i++]);
                    }
                }
                if(!find &&  i<l)
                {
                    if(n >= len[c])
                    {
                        cout << num << endl;
                        find = true;
                    }
                    for(++i; !find && i<l; ++i)
                    {
                        if(line[i]<'A')
                        {
                            int n1 = line[i++] - '0';
                            while(i<l && line[i] < 'A')
                            {
                                n1 = 10*n1 + line[i++] - '0';
                            }
                            while(!find && !stak.empty())
                            {
                                char c1 = stak.top();
                                c1 -= c1>'Z' ? 'a'-26 : 'A';
                                stak.pop();
                                ++ i;
                                if(n1>=len[c1] || (n1<len[c1] && !ass[c1].count(n1)))
                                {
                                    cout << num << endl;
                                    find = true;
                                }
                                else
                                {
                                    n1 = ass[c1][n1];
                                }
                            }
                            if(!find)
                            {
                                ass[c][n] = n1;
                            }
                        }
                        else
                        {
                            stak.push(line[i++]);
                        }
                    }
                }
                else
                {
                    len[c] = n;
                }
            }
            cin >> line;
        }
        if(!find)
        {
            cout << 0 << endl;
        }
    }
    return 0;
}