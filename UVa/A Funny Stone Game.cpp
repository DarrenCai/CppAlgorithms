/**
 * UVa1378/LA3668
 * 有趣的石子游戏
 * Beijing 2006
 */

#include <iostream>
using namespace std;

#define M 530
#define N 23
int sg[N], a[N], v[M], n, kase = 0;

void calcSG() {
    sg[0] = 0;
    for (int i=1; i<N; ++i) {
        for (int j=0; j<i; ++j) for (int k=0; k<=j; ++k) v[sg[j]^sg[k]] = i;
        for (int j=0; j<M; ++j) if (v[j] < i) {
            sg[i] = j;
            break;
        }
    }
}

void solve() {
    --n; int s = 0;
    for (int i=0; i<n; ++i) {
        cin >> a[i];
        if (a[i]&1) s ^= sg[n-i];
    }
    cin >> a[n];
    cout << "Game " << ++kase << ": ";
    if (s) for (int i=0; i<n; ++i) if (a[i]) {
        for (int j=i+1; j<=n; ++j) for (int k=j; k<=n; ++k) if ((sg[n-i]^sg[n-j]^sg[n-k]) == s) {
            cout << i << ' ' << j << ' ' << k << endl;
            return;
        }
    }
    cout << "-1 -1 -1" << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    calcSG();
    while (cin>>n && n) solve();
    return 0;
}