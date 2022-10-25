/**
 * UVa1405/LA4002
 * 最终的密码
 * Asia Danang 2007
 */

#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

#define M 205
#define N 105
char s[M*N], lock[M][N]; string d[2][N], *a; short c[M], t[N];

bool check(const string& a, const string& b, short k, short n) {
    for (short i=k-1; i>=0; --i) if (b[i] != a[n-k+i]) return false;
    return true;
}

void update(string& dst, const string& src) {
    if (src.size() < dst.size() || (src.size() == dst.size() && src < dst)) dst = src;
}

bool cmp(short i, short j) {
    return a[i].size() < a[j].size() || (a[i].size() == a[j].size() && a[i] < a[j]);
}

void dp(short i, short j) {
    string &s = d[i&1][j] = "", (&e)[N]=d[(i+1)&1], r = e[t[0]];
    for (short k=0; k<c[i]; ++k) s += lock[i][(j+k)%c[i]];
    for (short k=c[i], x=c[i+1]; k>0; --k) {
        while (x>=0 && e[t[x]].size()-k>r.size()) --x;
        for (short p=0; p<x; ++p) if (check(s, e[t[p]], k, c[i])) {
            update(r, e[t[x = p]].substr(k));
            while (x>0 && e[t[x-1]].size()==e[t[x]].size()) --x;
            break;
        }
    }
    s += r;
}

void solve() {
    cin >> s;
    short m = c[0] = 0;
    for (short i=0; s[i]; ++i) s[i] == ';' ? c[++m] = 0 : lock[m][c[m]++] = s[i];
    for (short i=0, x=m&1; i<c[m]; ++i) {
        d[x][i] = "";
        for (short j=0; j<c[m]; ++j) d[x][i] += lock[m][(i+j)%c[m]], t[j] = j;
    }
    a = d[m&1]; sort(t, t+c[m], cmp);
    for (short i=m-1; i>=0; --i) {
        for (short j=0; j<c[i]; ++j) dp(i, j);
        a = d[i&1]; for (short j=0; j<c[i]; ++j) t[j] = j; sort(t, t+c[i], cmp);
    }
    cout << d[0][t[0]] << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short t; cin >> t;
    while (t--) solve();
    return 0;
}