/**
 * UVa129
 * 困难的串
 */

#include <iostream>
using namespace std;

#define M 81
int n, l, c; char a[M];

bool check(int i) {
    for (int j=1, k=(i+1)>>1, x; j<=k; ++j) {
        for (x=0; x<j; ++x) if (a[i-x] != a[i-x-j]) break;
        if (x == j) return false;
    }
    return true;
}

void print(int m) {
    for (int i=0; i<m; ++i) {
        cout << a[i];
        if (i==63 || i+1==m) cout << endl;
        else if ((i&3) == 3) cout << ' ';
    }
    cout << m << endl;
}

bool dfs(int i=0) {
    for (int j=0; j<l; ++j) {
        a[i] = 'A' + j;
        if (!check(i)) continue;
        if (++c == n) {
            print(i+1);
            return true;
        }
        if (dfs(i+1)) return true;
    }
    return false;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n >> l && n) c = 0, dfs();
    return 0;
}