/**
 * UVa1435/LA4384
 * 名片切割
 * CERC 2008
 */

#include <iostream>
using namespace std;

bool find(int a, int b, int c) {
    for (int i=a; i<c; i += a) if ((c-i)%b == 0) return true;
    return false;
}

bool solve() {
    int a, b, c, d; cin >> a >> b >> c >> d;
    if (c*(long long)d % (a*(long long)b)) return false;
    if ((c%a==0 && d%b==0) || (c%b==0 && d%a==0)) return true;
    if (a == b) return false;
    int a1 = max(a, b), b1 = min(a, b);
    if (c%a==0 && c%b==0 && find(a1, b1, d)) return true;
    if (d%a==0 && d%b==0 && find(a1, b1, c)) return true;
    return false;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    int t; cin >> t;
    while (t--) cout << (solve() ? "YES" : "NO") << endl;
    return 0;
}