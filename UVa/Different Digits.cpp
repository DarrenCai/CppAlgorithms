/**
 * UVa1341/LA3262
 * 不同的数字
 * Shanghai 2004
 */

#include <iostream>
#include <cstring>
#include <string>
using namespace std;

#define N 66000
int r[N<<1], least[10][N], n;

int digits(int x) {
    bool f[10] = {0}; int cnt = 0;
    while (x > 0) f[x%10] = true, x /= 10;
    for (int i=0; i<10; ++i) if (f[i]) ++cnt;
    return cnt;
}

int phi() {
    int x = n, ans = n;
    for (int i=2; i*i <= x; ++i) if (x%i == 0) {
        ans = ans/i*(i-1);
        while (x%i == 0) x /= i;
    }
    if (x > 1) ans = ans/x*(x-1);
    return ans;
}

int pow(int x, int phi) {
    return r[x <= phi ? x : x%phi + phi];
}

int find(int d, int r) {
    int x = 0;
    for (int i=1; i<d; ++i) if (least[i][r]) {
        if (!x || least[i][r] < least[x][r]) x = i; 
    }
    return x;
}

bool cmp(const string& ans, int phi, int x, int y, int r) {
    if (ans.size() == 0) return true;
    for (int s = least[y][r%n], i=s-1; i>0 && r; i = least[y][r = (r - pow(s-1, phi)*y%n + n) % n] - 1)
        if (x+'0' < ans[s-i]) return true;
    return false;
}

void sol() {
    memset(least, 0, sizeof(least));
    int d = 0, p = phi(), sr = 1; string ans;
    r[0] = 1; for (int i=1, q=p<<1; i<q; ++i) r[i] = 10*r[i-1]%n;
    for (int i=1; !d; sr = (sr + pow(i++, p)) % n) {
        for (int j=1; !d && j<10; ++j) {
            int v = n - sr*j % n, x = find(10-j, v);
            if (x) {
                char ch = '0' + (d = j);
                for (int k=0; k<i; ++k) ans += ch;
                for (int y; y = least[x][v]; v = (v - pow(y-1, p)*x%n + n) % n) ans[i-y] += x;
            }
        }
        for (int j=1, v; j<10; ++j) {
            for (int k=0; k<n; ++k) least[0][k] = least[j][k];
            if (!least[j][v = pow(i-1, p)*j%n]) least[j][v] = i;
            for (int k=1, x; k<n; ++k) if (least[0][k] && !least[0][x=(k+v)%n]) least[j][x] = i;
        }
        for (int j=1, x = d ? d+1 : 10; j<x; ++j) for (int k=0, v, y; k<j; ++k)
        if (least[y = j-k][(v = n-sr*k%n) % n] == i && cmp(ans, p, k, y, v)) {
            char ch = '0' + k;
            if (d) for (int q=0; q<i; ++q) ans[q] = ch;
            else for (int q=0; q<i; ++q) ans += ch;
            for (int z=i; v; z = least[y][v = (v - pow(z-1, p)*y%n + n) % n]) ans[i-z] += y;
            x = d = j;
            break;
        }
    }
    cout << ans;
}

void solve() {
    int c = digits(n);
    if (c > 1) {
        if (n%10==0 || n%16==0 || n%25==0) {
            if (c > 2) sol();
            else cout << n;
        } else {
            int d = 0, r = 1, sr = 1;
            for (int i=2; !d; ++i) {
                r = 10*r%n; sr = (sr + r) % n;
                for (int j=1; j<10; ++j) if (sr*j%n == 0) {
                    d = j;
                    for (int k=0; k<i; ++k) cout << d;
                    break;
                }
            }
        }
    } else cout << n;
    cout << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin>>n && n) solve();
    return 0;
}