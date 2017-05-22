/**
 * UVa10129
 * 单词
 */

#include <iostream>
#include <string>
#include <map>
#include <set>

using namespace std;

void search(map<char, set<char> > &g, char k)
{
    if(g.count(k)) {
        set<char> s = g[k]; g.erase(k);
        for (set<char>::iterator it = s.begin(); it != s.end(); ++it)
        {
            if (g.count(*it))
            {
                g[*it].erase(k);
                search(g, *it);
            }
        }
    }
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int d[26][2] = {0}, f1 = 0, f2 = 0, n;
        map<char, set<char> > g;
        cin >> n;
        while (n--)
        {
            string s;
            cin >> s;
            char a = s[0] - 'a', b = *s.rbegin() - 'a';
            ++d[a][0];
            ++d[b][1];
            g[a].insert(b);
            g[b].insert(a);
        }
        for (int i = 0; i < 26 && f1 < 2 && f2 < 2; ++i)
        {
            if (d[i][0] > d[i][1] + 1 || d[i][0] + 1 < d[i][1])
                f1 = 2;
            if (d[i][0] == d[i][1] + 1)
                ++f1;
            if (d[i][0] + 1 == d[i][1])
                ++f2;
        }
        if ((f1 == 0 && f2 == 0) || (f1 == 1 && f2 == 1))
        {
            search(g, g.begin()->first);
        }
        cout << (g.empty() ? "Ordering is possible." : "The door cannot be opened.") << endl;
    }
    return 0;
}