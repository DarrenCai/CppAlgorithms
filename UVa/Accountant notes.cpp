/**
 * UVa1441/LA4619
 * CERC 2009
 */

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

#define EQ -1000000001
#define ED -1000000002
#define N 50010
#define L 6000060
unordered_map<int, int> ch[L]; int d[L], f[L], vis[L], q[L], ans[N], m[N], n, t; vector<int> g[L]; string s;

void solve() {
    cin >> n;
    f[t = 1] = vis[1] = 0; ch[d[1] = 1].clear();
    for (int i=1; i<=n; ++i) {
        unordered_map<string, int> p; int a = ans[i] = 0, x = 1; char _; cin >> m[i];
        for (int j=0; j<m[i]; ++j) {
            cin >> s; isdigit(s[0]) ? q[a++] = -atoi(s.c_str()) : (q[a] = p.count(s) ? a-p[s] : a+1, p[s] = a++);
            q[a++] = EQ;
            cin >> _ >> s; isdigit(s[0]) ? q[a++] = -atoi(s.c_str()) : (q[a] = p.count(s) ? a-p[s] : a+1, p[s] = a++);
            if (cin.peek() == '\n') { q[a++] = ED; continue; }
            cin >> _ >> s; isdigit(s[0]) ? q[a++] = -atoi(s.c_str()) : (q[a] = p.count(s) ? a-p[s] : a+1, p[s] = a++);
            q[a++] = ED;
        }
        for (int j=0, p=2; j<a; x = ch[x][q[j++]], ++p)
            if (!ch[x].count(q[j])) vis[ch[x][q[j]] = ++t] = 0, d[t] = p, ch[t].clear(), g[t].clear();
        g[x].push_back(i);
    }
    int head = 0, tail = 0;
    for (unordered_map<int, int>::iterator it = ch[1].begin(); it != ch[1].end(); ++it) f[q[tail++] = it->second] = 1;
    while (head < tail) {
        int u = q[head++];
        for (unordered_map<int, int>::iterator it = ch[u].begin(); it != ch[u].end(); ++it) {
            int v = f[u]; while (v && !ch[v].count(min(d[v], it->first))) v = f[v];
            f[q[tail++] = it->second] = v ? ch[v][min(d[v], it->first)] : 1;
        }
    }
    unordered_map<string, int> p; int a = 0; char _; cin >> m[0];
    for (int i=0; i<m[0]; ++i) {
        cin >> s; isdigit(s[0]) ? q[a++] = -atoi(s.c_str()) : (q[a] = p.count(s) ? a-p[s] : a+1, p[s] = a++);
        q[a++] = EQ;
        cin >> _ >> s; isdigit(s[0]) ? q[a++] = -atoi(s.c_str()) : (q[a] = p.count(s) ? a-p[s] : a+1, p[s] = a++);
        if (cin.peek() == '\n') { q[a++] = ED; continue; }
        cin >> _ >> s; isdigit(s[0]) ? q[a++] = -atoi(s.c_str()) : (q[a] = p.count(s) ? a-p[s] : a+1, p[s] = a++);
        q[a++] = ED;
    }
    for (int i=0, x=1, p=2; i<a; ++i) {
        while (x && !ch[x].count(min(d[x], q[i]))) x = f[x];
        x = x ? ch[x][min(d[x], q[i])] : 1;
        for (int j=x; j && !vis[j]; vis[j] = 1, j = f[j])
            for (int k=g[j].size()-1; k>=0; --k) if (!ans[g[j][k]]) ans[g[j][k]] = p;
        if (q[i] == ED) ++p;
    }
    for (int i=1; i<=n; ++i) ans[i] ? cout << ans[i]-m[i] << endl : cout << "NONE" << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}