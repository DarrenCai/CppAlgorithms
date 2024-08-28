/**
 * UVa1662/LA3513
 * 括号
 * NEERC 2005
 */

#include <iostream>
using namespace std;

#define N 1004
char s[N]="(", p[N]; int l[N]; bool rm[N], f[N];

void solve() {
    for (int i=1, t=0; s[i]; ++i) {
        if (s[i] == '(') l[++t] = i, rm[i] = false, f[t] = false;
        else if (s[i] == ')') {
            char p = s[l[t--]-1], n = s[i+1]; rm[i] = false;
            if ((p!='*' && p!='/' && n!='*' && n!='/') || !f[t+1]) rm[l[t+1]] = rm[i] = true, f[t] |= f[t+1];
        } else if (s[i] == '+' || s[i] == '-') f[t] = true;
    }
    p[0] = p[1] = '(';
    for (int i=1, t=1; s[i]; ++i) {
        if (s[i] == '(') {
            if (!rm[i]) cout << s[i], p[t] = s[i];
            p[t+1] = p[t]; ++t;
        } else if (s[i] == ')') {
            if (!rm[i]) cout << s[i];
            --t;
        } else if (s[i] == '+' || s[i] == '-') p[t] = p[t-1]!='-' ? s[i] : '+' + '-' - s[i], cout << p[t];
        else if (s[i] == '*' || s[i] == '/') p[t] = p[t-1]!='/' ? s[i] : '*' + '/' - s[i], cout << p[t];
        else cout << s[i];
    }
    cout << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> s+1) solve();
    return 0;
}