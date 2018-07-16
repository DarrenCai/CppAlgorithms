/**
 * UVa690
 * 流水线调度
 */

#include <iostream>
#include <cstring>
using namespace std;

short n, ans; int p[5]; char c, jump[20];

bool ok(int *s, int k) {
    for (char i=0; i<5; ++i)
        if ((s[i]>>k) & p[i]) return false;
    return true;
}

void dfs(int *s, int d=1, int sum=n) {
    if (sum + jump[0]*(10-d) >= ans) return;
    if (d == 10) {
        if (sum < ans) ans = sum;
        return;
    }
    for (int i=0; i<c; ++i)
        if (ok(s, jump[i])) {
            int pp[5];
            for (int j=0; j<5; ++j) pp[j] = (s[j]>>jump[i]) | p[j];
            dfs(pp, d+1, sum + jump[i]);
        }
}

int main()
{
    while (cin>>n && n) {
        c = 0; ans = 10*n;
        memset(p, 0, sizeof(p));
        for (short i=0; i<5; ++i) 
            for (short j=0; j<n; ++j) {
                char c; cin >> c;
                if (c == 'X') p[i] |= 1<<j;
            }
        for (short i=0; i<=n; ++i)
            if (ok(p, i)) jump[c++] = i;
        dfs(p);
        cout << ans << endl;
    }
    return 0;
}