/**
 * UVa247
 * 电话圈
 */

#include <iostream>
#include <string>
#include <map>
using namespace std;

#define N 30
bool g[N][N]; short t, p[N];
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
        for (short i=0; i<n; ++i) for (short j=0; j<n; ++j) g[i][j] = i==j;
        for (short i=0; i<m; ++i) {
            cin >> s;
            short j=id(s);
            cin >> s;
            short k = id(s);
            g[j][k] = true;
        }
        for (short k=0; k<t; ++k) for (short i=0; i<t; ++i) for (short j=0; j<t; ++j)
            g[i][j] = g[i][j] || (g[i][k] && g[k][j]);
        for (short i=0; i<t; ++i) for (short j=0; j<=i; ++j) if (g[i][j] && g[j][i]) {
            p[i] = j;
            break;
        }
        if (kase) cout << endl;
        cout << "Calling circles for data set " << ++kase << ':' << endl;
        for (short i=0; i<t; ++i) {
            short cnt = 0;
            for (short j=i; j<t; ++j) if (p[j] == i) {
                if (cnt++) cout << ", ";
                cout << names[j];
            }
            if (cnt) cout << endl;
        }
    }
    return 0;
}