/**
 * UVa1627
 * 团队分组
 */

#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

#define abd(x1, x2) (x1>x2 ? x1-x2 : x2-x1)
#define N 105
struct part {
    vector<short> t[2];
    const short d() const { return abd(t[0].size(), t[1].size());}
    const short a() const { return t[0].size() + t[1].size(); }
} p[N];

bool g[N][N], visit[N], ok; vector<short> s[N]; short n, tt, team[N], dp[N][N], ans[N][N];

bool add(short v, short t, part& pt) {
    pt.t[t].push_back(v); team[v] = t; visit[v] = true;
    for (short i=s[v].size()-1; i>=0; --i)
        if (!visit[s[v][i]]) {
            for (short j=pt.t[1^t].size()-1; j>=0; --j)
                if (!g[s[v][i]][pt.t[1^t][j]] || !g[pt.t[1^t][j]][s[v][i]]) return false;
            if (!add(s[v][i], 1^t, pt)) return false;
        } else if (team[s[v][i]] != (1^t)) return false;
    return true;
}

void get(vector<short> (&t)[2], short i, short j) {
    if (i < j) {
        get(t, i, ans[i][j]);
        if (t[0].size() > t[1].size()) t[0].swap(t[1]);
        get(t, ans[i][j]+1, j);
    } else {
        if (p[i].t[0].size() < p[i].t[1].size()) p[i].t[0].swap(p[i].t[1]);
        t[0].insert(t[0].end(), p[i].t[0].begin(), p[i].t[0].end());
        t[1].insert(t[1].end(), p[i].t[1].begin(), p[i].t[1].end());
    }
}

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short t; cin >> t;
    while (t--) {
        tt = 0; memset(g, false, sizeof(g)); memset(visit, false, sizeof(visit)); ok = true; cin >> n;
        for (short i=1; i<=n; ++i) {
            s[i].clear(); short j; while (cin>>j && j) g[i][j] = true;
        }
        for (short i=1; i<n; ++i) for (short j=i+1; j<=n; ++j)
            if (!g[i][j] || !g[j][i]) s[i].push_back(j), s[j].push_back(i);
        for (short i=1; i<n; ++i) if (s[i].size() > 0 && !visit[i]) {
            part pp;
            if ((ok = add(i, 0, pp))) p[tt++] = pp;
            else break;
        }
        if (!ok) {
            cout << "No solution" << endl;
        } else {
            for (short i=tt-1; i>=0; --i) dp[i][i] = p[i].d();
            for (short l=1; l<tt; ++l) for (short i=0; i+l<tt; ++i) {
                short j = i+l; dp[i][j] = abd(dp[i][i], dp[i+1][j]); ans[i][j] = i;
                for (short k=i+1; k<j; ++k) {
                    short v = abd(dp[i][k], dp[k+1][j]);
                    if (v < dp[i][j]) dp[i][j] = v, ans[i][j] = k;
                }
            }
            short d=tt > 0 ? dp[0][tt-1] : 0;
            vector<short> tp[2]; if (tt > 0) get(tp, 0, tt-1);
            short s = tp[0].size() + tp[1].size(), st = tp[0].size() <= tp[1].size() ? 0 : 1,
                r = n-s, m = r > d ? (r+d)>>1 : r;
            for (short i=1, c=0; i<=n; ++i) if (!visit[i]) tp[++c > m ? 1^st : st].push_back(i);
            cout << tp[0].size();
            for (short i=tp[0].size()-1; i>=0; --i) cout << ' ' << tp[0][i];
            cout << endl << tp[1].size();
            for (short i=tp[1].size()-1; i>=0; --i) cout << ' ' << tp[1][i];
            cout << endl;
        }
        if (t) cout << endl;
    }
    return 0;
}
