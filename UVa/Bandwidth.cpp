/**
 * UVa140
 * 带宽
 */

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

vector<char> g[26], v; char n, s[8], s1[8], p[8], m[8]={1,1,1,1,1,1,1,1}, mi; bool visit[26] = {false};

void dfs(char cur) {
    if (cur == n) {
        char mmax = m[0];
        for (char i=1; i<n; ++i) mmax = max(mmax, m[i]);
        if (mmax < mi || !mi) {
            mi = mmax;
            for (char i=0; i<n; ++i) s1[i] = s[i];
        }
    } else for (char i=0; i<n; ++i) {
        if (!visit[i]) {
            visit[i] = true;
            s[cur] = i;
            p[i] = cur;
            char t = 0, len = g[v[i]].size();
            for (char j=0; j<len; ++j) if (!visit[g[v[i]][j]]) ++t;
            bool ok = !mi || t<mi;
            for (char j=0; ok && j<cur; ++j) {
                if (find(g[v[i]].begin(), g[v[i]].end(), v[s[j]]) != g[v[i]].end()) {
                    char d = max(p[s[j]]-p[i], p[i]-p[s[j]]);
                    m[i] = max(m[i], d);
                    if (mi && m[i]>=mi) ok = false;
                }
            }
            if (ok) dfs(cur+1);
            m[i] = 1;
            visit[i] = false;
        }
    }
}

int main()
{
    string s;
    while (cin>>s && s[0]!='#') {
        s += ';';
        const char len = s.length();
        for (char i=0; i<len; ++i) {
            if (s[i]!=';' && s[i]!=':') {
                char c = s[i]-'A';
                v.push_back(c);
                if (s[i+1] == ':') {
                    ++ i;
                    while(s[++i] != ';') {
                        char c1= s[i]-'A';
                        v.push_back(c1);
                        if (find(g[c].begin(), g[c].end(), c1) == g[c].end())
                            g[c].push_back(c1);
                        if (find(g[c1].begin(), g[c1].end(), c) == g[c1].end())
                            g[c1].push_back(c);
                    }
                }
            }
        }
        sort(v.begin(), v.end());
        n = unique(v.begin(), v.end()) - v.begin();
        mi = 0;
        dfs(0);
        for (char i=0; i<n; ++i) cout << char(v[s1[i]]+'A') << ' ';
        cout << "->" << ' ' << short(mi) << endl;
        v.clear();
        for (char i=0; i<26; ++i) g[i].clear();
    }
    return 0;
}