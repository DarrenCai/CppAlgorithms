/**
 * UVa1415/LA4079
 * 高斯素数
 * Changchun 2007
 * 知识点：高斯素数的两个条件 https://blog.csdn.net/weixin_45697774/article/details/113444562
 */

#include <iostream>
using namespace std;

#define M 132
#define N 17321
int prim[2000], n = 0; bool f[N] = {false};

int is_prim(int x) {
    if (x < N) return !f[x];
    for (int i=0; i<n; ++i) if (x%prim[i] == 0) return false;
    return true;
}

bool solve() {
    int a, b; cin >> a >> b;
    if (a == 0) return b == 1; // return false;
    return is_prim(a*a + 2*b*b);
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    for (int i=2; i<M; ++i) if (!f[i]) for (int j=i*i; j<N; j+=i) f[j] = true;
    for (int i=2; i<N; ++i) if (!f[i]) prim[n++] = i;
    int t; cin >> t;
    while (t--) cout << (solve() ? "Yes" : "No") << endl;
    return 0;
}