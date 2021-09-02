/**
 * UVa247
 * 电话圈
 */

#include <iostream>
#include <cstring>
#include <string>
#include <map>
using namespace std;

#define N 30
bool g[N][N], visit[N]; short t;
map<string, int> ids; string names[N], s;

short id(const string& name) {
    if (ids.count(name)) return ids[name];
    names[t] = name;
    return ids[name] = t++;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short n, m, kase;
    while (cin>>n>>m && n) {
        t = 0; ids.clear();
        memset(g, 0, sizeof(g));
        memset(visit, 0, sizeof(visit));
        for (short i=0; i<m; ++i) {
            cin >> s;
            short j=id(s);
            cin >> s;
            short k = id(s);
            g[j][k] = true;
        }
        for (short k=0; k<t; ++k) for (short i=0; i<t; ++i) for (short j=0; j<t; ++j)
            g[i][j] = g[i][j] || (g[i][k] && g[k][j]);
        if (kase) cout << endl;
        cout << "Calling circles for data set " << ++kase << ':' << endl;
        for (short i=0; i<t; ++i) {
            if (visit[i]) continue;
            cout << names[i];
            for (short j=i+1; j<t; ++j) if (!visit[j] && g[i][j] && g[j][i]) {
                cout << ", " << names[j];
                visit[j] = true;
            }
            cout << endl;
        }
    }
    return 0;
}