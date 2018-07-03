/**
 * UVa208
 * 消防车
 */

#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

bool s[21][21], reach[21]; short k, m=0, r, path[21];

void bfs() {
    reach[1] = true;
    queue<char> q; q.push(1);
    while (!q.empty() && !reach[k]) {
        char f = q.front(); q.pop();
        for (char i=2; i<=m; ++i)
            if (!reach[i] && s[f][i]) {
                reach[i] = true; q.push(i);
            }
    }
}

void dfs(char d=0) {
    for (char i=2; i<=m; ++i)
        if (!reach[i] && s[path[d]][i]) {
            path[d+1] = i; reach[i] = true;
            if (i == k) {
                for (char j=0; j<=d; ++j)
                    cout << path[j] << ' ';
                cout << k << endl; ++r;
            }
            dfs(d+1); reach[i] = false;
        }
}

int main()
{
    short t=0;
    while (cin>>k) {
        cout << "CASE " << ++t << ':' << endl;
        memset(s, false, sizeof(s));
        memset(reach, false, sizeof(reach));
        short a, b;
        while (cin>>a>>b && a) {
            s[a][b] = true; s[b][a] = true;
            m = max(m, max(a, b));
        }
        bfs();
        if (reach[k]) {
            memset(reach, false, sizeof(reach));
            path[0] = 1; r = 0; reach[1] = true;
            dfs();
            cout << "There are " << r << " routes from the firestation to streetcorner " << k << '.' << endl;
        } else {
            cout << "There are 0 routes from the firestation to streetcorner " << k << '.' << endl;
        }
    }
    return 0;
}