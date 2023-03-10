/**
 * UVa1434/LA4382
 * CERC 2008
 * 知识点：（威尔逊定理，质数判定的充要条件）https://en.wikipedia.org/wiki/Wilson%27s_theorem
 */

#include <iostream>
using namespace std;

#define M 1732
#define N 1000007
#define T 3000030
int s[N]; bool f[T] = {false};

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    for (int i=2; i<M; ++i) if (!f[i]) for (int j=i*i; j<T; j+=i) f[j] = true;
    s[0] = 0;
    for (int i=1; i<N; ++i) s[i] = s[i-1] + !f[3*i+7];
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        cout << s[n] << endl;
    }
    return 0;
}